#ifndef pci_h
#define pci_h
#include <access.h>
 typedef struct pci_dev_s
 {
	 uint8 bus;
	 uint8 dev : 5;
	 uint8 multifunc : 2;
	 uint8 present : 1;
	 uint8 class,subclass;
 }__attribute__((packed)) pci_dev_t;

 typedef struct pci_bus_s
 {
	 uint8 bus;
	 pci_dev_t *devs;
 }__attribute__((packed)) pci_bus_t;
 
 #define pci_lst_len (256*32)
 
 #define pci_class(uint32val) (uint32val>>24)
 #define pci_subclass(uint32val) ((uint32val>>16)&0xff)
 #define pci_progIF(uint32val) ((uint32val>>8)&0xff)
 #define pci_revisionID(uint32val) (uint32val&0xff)
 #define pci_device_present(devstruct)((devstruct.bus+devstruct.dev+devstruct.func+devstruct.class+devstruct.subclass))
 
 Public void pci_init();
 Public void pci_enumerate();
 
 Public uint8 pci_checkbus(uint8 bus);
 Public pci_dev_t pci_checkdev(uint8 bus,uint8 dev);
 Public uint8 pci_isPciBridge(uint8 bus,uint8 dev,uint8 func);
 Public void pci_findBuses(uint16 bus);

 Public uint16 pci_configread16(uint16 bus, uint16 dev, uint16 func, uint16 offset);
 Public uint32 pci_configread32(uint16 bus, uint16 dev, uint16 func, uint16 offset); 

 #define pci_getPrimaryBus(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)&0xff)
 #define pci_getSecondaryBus(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)>>8)&0xff)
 #define pci_getSubordinateBus(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)>>16)&0xff)
 #define pci_getVendorID(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0)&0xffff)
 #define pci_getDeviceID(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0)>>16)&0xffff)
 #define pci_getHeaderType(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x0C)>>16)&0xff)
 #define pci_getClass(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(bus,dev,func,0x08)>>24)&0xff)
 #define pci_getSubClass(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(bus,dev,func,0x08)>>16)&0xff)
 
 
#endif
