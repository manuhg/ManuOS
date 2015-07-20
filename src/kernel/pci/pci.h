#ifndef pci_h
#define pci_h

#include <access.h>
 
 #define _pcie_base_addr_strct_size 16
 #define _pcie_base_addr_strcts_x86 2
 typedef struct pcie_confaddr_s
 {
	 uint64 *base_addr; //8 bytes base addr
	 uint16 seg_grp_num; //2 bytes segment group addr
	 uint8 bus_num_s; //starting bus number
	 uint8 bus_num_e; //ending bus number
	 uint32 reserved; //reserved
 }__attribute__((packed)) pcie_confaddr_t;
 
 typedef struct pci_addr_s
 {
	 uint8 reserved:2;
	 uint8 reg_no:6;
	 uint8 function:3;
	 uint8 device:5;
	 uint8 bus;
	 uint8 reserved_:7;
	 uint8 enable:1;
 }__attribute__((packed))pci_addr_t;
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
 
 #define pci_conf_reg 0xcf8
 #define pci_data_reg 0xcfc
 #define pci_lst_len (256*32)
 
 #define pci_write(_value)(outl(pci_conf_reg,_value))
 #define pci_read()(inl(pci_data_reg))
 #define pci_class(uint32val) (uint32val>>24)
 #define pci_subclass(uint32val) ((uint32val>>16)&0xff)
 #define pci_progIF(uint32val) ((uint32val>>8)&0xff)
 #define pci_revisionID(uint32val) (uint32val&0xff)
 #define pci_device_present(devstruct)((devstruct.bus+devstruct.dev+devstruct.func+devstruct.class+devstruct.subclass))
 
 Public void pci_init();
 Public void pcie_init();
 Public uint8 pci_getpcitype();
 Public void pci_print_info(uint8 bus,uint8 dev,uint8 func);
 
 Public uint8 pci_checkbus(uint8 bus);
 Public pci_dev_t pci_checkdev(uint8 bus,uint8 dev);
 Public uint8 pci_isPciBridge(uint8 bus,uint8 dev,uint8 func);
 #ifdef internal
   #undef internal
   #include <kernel/acpi.h>
   Public void pcie_find_bus_ranges(sdt_header_t *mcfg);
   #define internal
  #else
   #include <kernel/acpi.h>
   Public void pcie_find_bus_ranges(sdt_header_t *mcfg);
 #endif

 Public uint32 pci_configread32(uint8 bus, uint8 dev, uint8 func, uint8 offset); 

 #define pci_getPrimaryBus(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)&0xff)
 #define pci_getSecondaryBus(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)>>8)&0xff)
 #define pci_getSubordinateBus(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0x18)>>16)&0xff)
 #define pci_getVendorID(uint8_bus,uint8_dev,uint8_func) (pci_configread32(uint8_bus,uint8_dev,uint8_func,0)&0xffff)
 #define pci_getDeviceID(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0)>>16)&0xffff)
 #define pci_getHeaderType(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x0C)>>16)&0xff)
 #define pci_getClass(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x08)>>24)&0xff)
 #define pci_getSubClass(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x08)>>16)&0xff)
 #define pci_getProgIF(uint8_bus,uint8_dev,uint8_func) ((pci_configread32(uint8_bus,uint8_dev,uint8_func,0x08)>>8)&0xff)
 

#endif
