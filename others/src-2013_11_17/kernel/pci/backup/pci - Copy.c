#include <stdio.h>
#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/acpi.h>
#define internal
#include "pci.h"
uint8 pci[256];
uint8 *pcibus=pci;
pci_dev_t pci_devs[256*32];
pci_dev_t *pci_dev=pci_devs;
uint8 pos=0;
uint16 devs=0;
pcie_confaddr_t *bus_range[255];

extern uint32 read_data_port(uint32 Bus,uint32 Device,uint32 Function,uint32 vendorID);
void pci_init()
{
	printf("\n\t pci init");	
	pci_enumerate();
	pci_findBuses(0);
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
void pcie_find_bus_ranges(sdt_header_t *mcfg)
{
	int i=0;
	bus_range[0]=(pcie_confaddr_t *)mcfg+(mcfg->len);
	i=0;
	while(i<51)
	{
		++i;
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
/*void pci_enumerate()
{
	uint16 bus,dev,present=0,func,class;pci_dev_t a;
	for(bus=0;bus<256;bus++)
	{
		for(dev=0;dev<32;dev++)
		{
			a=pci_checkdev(bus,dev);
			if(a.present) //if device present
			{
				*pci_dev++=a;
				if(a.multifunc)
				{
					for(func=0;func<8;func++)
					{
						class=pci_getClass(a.bus,a.dev,func);
						if(class!=0xff)
						{
							present++;
							_print_int(class);
							outbyte('_');_print_int(func);outbyte(' ');
						}
					}
				}
				else
				{
					class=pci_getClass(a.bus,a.dev,func);
					if(class!=0xff)
					{
						present++;
						_print_int(class);
						_printf(" ");
					}
				}
			}
		}
	}
	_printf("\n\t ");_print_int(present);_printf(" devices are found");
}*/

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
void pci_findBuses(uint16 bus)//from the given bus, go finding it there are any more buses ahead of it
{
	uint16 a=0,k=0,sbus=0;
	*pcibus++=bus;_printf("\t ");
	while(1)
	{
		if(pci_getVendorID(bus,0,0)!=0xffff /*&& pci_getDeviceID(bus,0,0)==0xffff*/)
		{
			sbus=0;
			a=pci_configread32(bus,0,0,0x08);
			if(((a>>24)&0xff)==0x06&&((a>>16)&0xff)==0x04)
			{
				sbus=pci_getSecondaryBus(bus,0,0);
				if(pci_checkbus(sbus))
				 *pcibus++=sbus;					
				bus=sbus;				
			}
			k++;
		}
		else
		  break;
		
	}
	_printf("\n\t ");_print_int(k);_printf(" PCI buses found");
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

byte pci_getConf(byte Bus, byte Device, byte Function, struct PCIConfigurationSpace * PCICfg)
     {int Reg;
     int First=1;
     for ( Reg=0;Reg < sizeof(struct PCIConfigurationSpace) / sizeof(DWORD); Reg++ )
         {DWORD Addr,Value;
         Addr = 0x80000000L |
               ( ((DWORD) Bus) << 16 ) |
               ( ((DWORD)( Device << 3 ) | Function ) << 8) |
               ( Reg << 2 );

         OutPortDWord( PCI_CONFIG_ADDRESS, Addr);

         Value = InPortDWord(PCI_CONFIG_DATA);

         Addr = InPortDWord(PCI_CONFIG_ADDRESS);
         ((DWORD *)PCICfg)[Reg]=Value;
         OutPortDWord( PCI_CONFIG_ADDRESS, 0);
         if ( First )
            {if ( Value == 0xFFFFFFFF )
                return 0;
            First=0;
            }
         }
     return Reg;
     }
     
uint32 pci_configread32(uint16 bus, uint16 dev, uint16 func, uint16 offset)
{
	uint32 address;
    uint64_ lbus=(uint64_)bus;
    uint64_ ldev=(uint64_)dev;
    uint64_ lfunc=(uint64_)func;

    address = (uint32)((lbus << 16) | (ldev << 3) |(lfunc << 8) | (offset & 0xfc) | 0x80000000L );
    outl(0xCF8,address);
    return inl(0xCFC);
}

uint16 pci_configread16(uint16 bus, uint16 dev, uint16 func, uint16 offset)
{
    uint64_ address;
    uint64_ lbus=(uint64_)bus;
    uint64_ ldev=(uint64_)dev;
    uint64_ lfunc=(uint64_)func;
    uint16 tmp = 0;
 
    address = (uint64_)((lbus << 16) | (ldev << 11) | (lfunc << 8) | (offset & 0xfc) | (1<<31));
    outl(0xCF8, address);
    tmp = (uint16)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}
/*
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
*/
