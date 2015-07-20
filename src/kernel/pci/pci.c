#include <stdio.h>
#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/acpi.h>
#define internal
#include "pci.h"
#include "pci_classes.h"
uint8 pci[256];
uint8 *pcibus=pci;
pci_dev_t pci_devs[256*32];
pci_dev_t *pci_dev=pci_devs;
uint16 pos=0;
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
	
	printf("\n\t pci init\n ");
	PCI_Type=pci_getpcitype();	
	pcibus=pci;
	pci_checkbus(0);
	printf("\n\t:%d devices found,%d buses present",devs,pos+1);	
}
uint8 pci_checkbus(uint8 bus)
{
	uint8 dev=0;uint16 t=0; pci_dev_t a;
	for(dev=0;dev<32;dev++)
	{
		a=pci_checkdev(bus,dev);
		if(a.present)t++;
	}
	if(t)
	  return 1;
	return 0;
}
pci_dev_t pci_checkdev(uint8 bus,uint8 dev)
{
	uint8 func=0; pci_dev_t a;//uint8 i;
	a.bus=bus;
	a.dev=dev;
	a.multifunc=0;
	a.present=0;
	if((pci_getVendorID(bus,dev,0)==0xffff)||(pci_getClass(bus,dev,0)>0x11))
	 return a;
	a.present=1;
	printf("\n %d)",++devs);/*
	if(pci_getHeaderType(bus,dev,0)&0x80) //in 0x80 the 7th bit ,has multifunction
	{
		for(i=0;i<8;i++)
		  if((pci_getVendorID(bus,dev,i)!=0xffff)&&(pci_getClass(bus,dev,i)<0x12))
		    pci_isPciBridge(bus,dev,i);
	}
	*/
	switch(pci_getHeaderType(bus,dev,func)&0x7f) //see if it is pci-pci bridge
	{
		case 1:
		//printf("PCI-PCI ");
		pci_isPciBridge(bus,dev,func);
		pos++;
		break;
		default:
		break;
	}
	pci_print_info(bus,dev,func);
	//printf("%s->%d %d %d",class_code_str[pci_getClass(bus,dev,0)],pci_getClass(bus,dev,0),pci_getSubClass(bus,dev,0),pci_getDeviceID(bus,dev,0));
	return a;	
}

void pci_print_info(uint8 bus,uint8 dev,uint8 func)
{
	uint32 class,subclass,progif,i;
	class=pci_getClass(bus,dev,func);
	subclass=pci_getSubClass(bus,dev,func);
	progif=pci_getProgIF(bus,dev,func);
	for(i=0;i<PCI_CLASSCODETABLE_LEN;i++)
	{
		if(class==PciClassCodeTable[i].BaseClass)
		  if(subclass==PciClassCodeTable[i].SubClass)
		    if(progif==PciClassCodeTable[i].ProgIf)
		     printf("%s=>%s %s",PciClassCodeTable[i].BaseDesc,PciClassCodeTable[i].SubDesc,PciClassCodeTable[i].ProgDesc);
	}
}
uint8 pci_isPciBridge(uint8 bus,uint8 dev,uint8 func)
{
	uint8 secondarybus=0;
	if(pci_getHeaderType(bus,dev,func)&0x7f)
	if((pci_getClass(bus,dev,func)==0x06)&&(pci_getSubClass(bus,dev,func)==0x04))
	{
		secondarybus=pci_getSecondaryBus(bus,dev,func);
		printf("'%d': ",secondarybus);
		pcibus[pos++]=secondarybus;
		//if(pci_checkbus(secondarybus))
		 // return secondarybus;
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

//#ifdef _inclunusables
/**
void print_pci_inf(sdt_header_t *ptr)
{
	pcie_confaddr_t *pcie_baseaddr;
	printf("\n\t Length of MCFG = %d str=%s",(int)ptr->len,ptr->signature);
	pcie_baseaddr=(pcie_confaddr_t *)(ptr)+0x2c;
	printf(" Base address of PCIe= ");_print_hex((uint64_t)_ptr_conv pcie_baseaddr->base_addr);
	printf("\n Seg grp num : %d , buses from %d to %d ",pcie_baseaddr->seg_grp_num,pcie_baseaddr->bus_num_s,pcie_baseaddr->bus_num_e);
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

void pcie_init()
{
	pcie_confaddr_t *pcie_baseaddr;
	if(mcfg_pci)
	{
		printf("\n mcfg table found\n :");
		puts_sl((char *)mcfg_pci,60);
		printf("\n----------\n");
	}
	else
	{
		sdt_header_t *mcfg=acpi_getsdt("MCFG");
		//read_data_port(0,1,1,0);
		printf("\n\t Locating PCI Express Extended configuration space");
		if(!mcfg)
		{
			mcfg=mcfg_pci;
			if(!mcfg)
			{
				mprintf(error_text_colour,"\n\t Non existant or Invalid ACPI MCFG Table ");
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
	}
	printf("\n\t Length of MCFG = %d str=%s",(int)mcfg_pci->len,mcfg_pci->signature);
	pcie_baseaddr=(pcie_confaddr_t *)(mcfg_pci)+0x2c;
	printf(" Base address of PCIe= ");_print_hex((uint64_t)_ptr_conv pcie_baseaddr->base_addr);
	printf("\n Seg grp num : %d , buses from %d to %s ",
	pcie_baseaddr->seg_grp_num,pcie_baseaddr->bus_num_s,pcie_baseaddr->bus_num_e);
	//bus_range[0]=(pcie_confaddr_t *)mcfg+(mcfg->len);
	//printf("\n\t Found buses from : %d-%d ,",bus_range[0]->bus_num_s,bus_range[0]->bus_num_e);
	//pcie_find_bus_ranges(mcfg);
}*/
//#endif
