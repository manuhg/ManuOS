#include <stdio.h>
#include <portio.h>
#define internal
#include "pci.h"
uint8 pci[256];
uint8 *pcibus=pci;
pci_dev_t pci_devs[256*32];
pci_dev_t *pci_dev=pci_devs;
uint8 pos=0;
uint16 devs=0;
void pci_init()
{
	_printf("\n\t pci init");	
	pci_enumerate();
	pcibus=pci;
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
	_printf("\n\t ");_print_int(present);_printf(" buses found");
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

uint32 pci_configread32(uint16 bus, uint16 dev, uint16 func, uint16 offset)
{
	uint64_ address;
    uint64_ lbus=(uint64_)bus;
    uint64_ ldev=(uint64_)dev;
    uint64_ lfunc=(uint64_)func;

    address = (uint64_)((lbus << 16) | (ldev << 11) |(lfunc << 8) | (offset & 0xfc) | ((uint32)0x80000000) );
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
 
    address = (uint64_)((lbus << 16) | (ldev << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32)0x80000000));
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
