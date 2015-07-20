#include <stdio.h>
#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/acpi.h>
#define internal
#include "pci.h"
uint8 pci[256];
uint8 *pcibus=pci;
//pci_dev_t pci_devs[256*32];
//pci_dev_t *pci_dev=pci_devs;
uint8 pos=0;
uint16 devs=0;
pcie_confaddr_t *bus_range[_pcie_base_addr_strcts_x86];
uint8 PCI_Type=0;
extern uint32 read_data_port(uint32 Bus,uint32 Device,uint32 Function,uint32 vendorID);
char *class_code_str[18]=
{
	 " Device was built prior definition of the class code field",
	 " Mass Storage Controller",
	 " Network Controller",
	 " Display Controller",
	 " Multimedia Controller",
	 " Memory Controller",
	 " Bridge Device",
	 " Simple Communication Controllers",
	 " Base System Peripherals",
	 " Input Devices",
	 " Docking Stations",
	 " Processors",
	 " Serial Bus Controllers",
	 " Wireless Controllers",
	 " Intelligent I/O Controllers",
	 " Satellite Communication Controllers",
	 " Encryption/Decryption Controllers",
	 " Data Acquisition and Signal Processing Controllers" 
};
void pci_init()
{
	
	printf("\n\t pci init");
	PCI_Type=pci_getpcitype();
	//pci_enumerate();
	//pci_findBuses(0);
	pci_regpci_init();
	pcibus=pci;
	pcie_init();
	
}
void pcie_init()
{
	sdt_header_t *mcfg=acpi_getsdt("MCFG");
	read_data_port(0,1,1,0);
	printf("\n\t Locating PCI Express Extended configuration space");
	if(!mcfg)
	{
		mcfg=mcfg_pci;
		if(!mcfg)
		{
			mprintf(error_text_colour,"\n\t Unable to locate PCI Express Extended configuration space");
			return;
		}	
	}
	if(((bytesum((phys_addr *) _ptr_conv mcfg,mcfg->len))&0xff)!=0)
	{		
		mcfg=mcfg_pci;
		if(!mcfg || (((bytesum((phys_addr *) _ptr_conv mcfg,mcfg->len))&0xff)!=0))
		{
			mprintf(error_text_colour,"\n\t Invalid ACPI MCFG Table");
			return;
		}
	}
	bus_range[0]=(pcie_confaddr_t *)mcfg+(mcfg->len);
	printf("\n\t Found buses from : %d-%d ,",bus_range[0]->bus_num_s,bus_range[0]->bus_num_e);
	pcie_find_bus_ranges(mcfg);
}
void pci_regpci_init()
{
	int i,j=0,k=0,h=0;uint16 tmp=0;
	printf("\n");
	for(i=0;i<32;i++)
	{
		 //if(pci_getVendorID(0,i,0)==0xffff)
		  //break;
		 h=pci_getHeaderType(0,i,0);
		 /*if(h&0x80) h=8;
		 else */h=1;
		 for(k=0;k<h;k++)
		 {
			 tmp=pci_getClass(0,i,k);
			 if(tmp<18)
			 {
				 j++;
				 switch(((pci_getHeaderType(0,i,k))&0x7f))//omit the 7th bit
				 {
					 case 1:
					 printf("\t %d)PCI-PCI %s",j,class_code_str[tmp]);
					 break;
					 case 2:
					 printf("\t %d)Cardbus %s",j,class_code_str[tmp]);
					 default:
					 printf("\t %d)%s,",j,class_code_str[tmp]);
				 }
				 printf(" %d %d",pci_getSubClass(0,i,k),pci_getProgIF(0,i,k));			 
			 }
		 }
	}
	printf("\n\t Number of devices present in Bus number 0 = ");
	printf("%d",j);
}
void pcie_find_bus_ranges(sdt_header_t *mcfg)
{
	int i=0;
	bus_range[0]=(pcie_confaddr_t *)mcfg+(mcfg->len);
	i=0;
	while(++i<_pcie_base_addr_strcts_x86)
	{
		bus_range[i]=bus_range[0]+(_pcie_base_addr_strct_size*i);
		printf(" %d-%d ,",bus_range[i]->bus_num_s,bus_range[i]->bus_num_e);
	}
}
void pci_enumerate()
{
	uint16 bus=0,present=0;
	for(bus=0;bus<256;bus++)
	{
		if(pci_checkbus((uint8)bus))
		{
			present++;
			pci[bus]=1;
		}
	}
	printf("\n\t %d buses found",present);
}

uint8 pci_checkbus(uint8 bus)
{
	uint8 dev=0,t=0; pci_dev_t a;
	for(dev=0;dev<32;dev++)
	{
		a=pci_checkdev(bus,dev);
		if(a.present)
		 t++;		 
		else
		 break;
	}
	devs+=t;
	if(t>0)
	  return 1;
	return 0;
}

pci_dev_t pci_checkdev(uint8 bus,uint8 dev)
{
	uint8 func=0; pci_dev_t a;
	a.bus=bus;
	a.dev=dev;
	a.multifunc=0;
	a.present=0;
	if(pci_getVendorID(bus,dev,0)==0xffff)
	 return a;
	else
	 a.present=1;
	if(pci_getHeaderType(bus,dev,0)&0x80) //in 0x80 the 7th bit is set. if it is done in the reg, then it has multifunction
	{
		func=0;
		while(func<8)
		{
			if(pci_getVendorID(bus,dev,func)!=0xffff)
			{
				a.present=0;
				break;
			}
			a.present=1;/*		
			if(pci_isPciBridge(bus,dev,func)) //see if it is pci-pci bridge
			 pcibus[pos++]=pci_getSecondaryBus(bus,dev,func);*/			
			a.multifunc+=1; 
			func++;
		}
	}
	a.class=pci_getClass(bus,dev,0);
	a.subclass=pci_getSubClass(bus,dev,0);
	
	
	return a;	
}
void pci_findBuses(uint8 bus)//from the given bus, go finding it there are any more buses ahead of it
{
	if(bus){}
}
uint8 pci_isPciBridge(uint8 bus,uint8 dev,uint8 func)
{
	uint8 secondarybus=0;
	if((pci_getClass(bus,dev,func)==0x06)&&(pci_getSubClass(bus,dev,func)==0x04))
	{
		secondarybus=pci_getSecondaryBus(bus,dev,func);
		if(pci_checkbus(secondarybus))
		  return secondarybus;
	 }
	return 0;
}
uint32 pci_configread32(uint8 bus, uint8 dev, uint8 func, uint8 offset)
{
	uint32 address;
    address = (uint32)((bus << 16) | (dev << 11) |(func << 8) | (offset) | 0x80000000 );
    pci_write(address);
    return pci_read();
}
uint8 pci_getpcitype()
{
	uint8 type=0;uint32 tmp;
	outl(0xcf8,0);
	outl(0xcfa,0);
	if(inl(0xcf8)==0&&inl(0xcfa))
	 type=2;
	else
	{
		tmp=inl(0xcf8);
		outl(0xcf8,0x80000000);
		if(inl(0xCF8)==0x80000000)
		 type=1;
		outl(0xcf8,tmp);
	}
	return type;
}
