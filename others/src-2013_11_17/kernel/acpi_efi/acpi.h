#ifndef acpi_h
#define acpi_h
#include <access.h>
 #include <kernel/memory.h>
 #define _acpi_rsdp_sig "RSD PTR "
 #define _xsdt_entries(len) ((int)((len-sizeof(sdt_header_t))/sizeof(uint64)))
 typedef struct rsdp_desc_s
 {
	 char signature[8];
	 uint8 checksum;
	 char OEMID[6];
	 uint8 revision;
	 uint32 rsdt_addr;	 
	 uint32 len;
	 uint64 xsdt_addr;
	 uint8 ext_checksum;
	 uint8 reserved[3];
  }__attribute__((packed))rsdp_desc_t;
  
  typedef struct sdt_header_s
  {
	  char signature[4];
	  uint32 len;
	  uint8 revision;
	  uint8 checksum;
	  char OEMID[6];
	  char OEMtableID[8];
	  uint32 OEMrevision;
	  uint32 creatorID;
	  uint32 creatorRevision;
  }__attribute__((packed))sdt_header_t;
 
typedef struct facp_s
{
   uint8 Signature[4];
   uint32 Length;
   uint8 unneded1[40 - 8];
   uint64 *DSDT;
   uint8 unneded2[48 - 44];
   uint64 *SMI_CMD;
   uint8 ACPI_ENABLE;
   uint8 ACPI_DISABLE;
   uint8 unneded3[64 - 54];
   uint64 *PM1a_CNT_BLK;
   uint64 *PM1b_CNT_BLK;
   uint8 unneded4[89 - 72];
   uint8 PM1_CNT_LEN;
}__attribute__((packed))facp_t;
 
  typedef struct xsdt_s
  {
	  sdt_header_t header;
	  uint64 *other_tables[20];//there are (i tink so) 20 tables excluding xsdt and rsdt but this value is not used in any other place
  }__attribute__((packed))xsdt_t;
  
  typedef struct sdtlst_s
  {
	  char sig[20][4];
	  sdt_header_t header[20];
  }__attribute__((packed))sdtlst_t;
 Public void acpi_init();
 Public uint8 acpi_parseDSDT();
 Public sdt_header_t *acpi_findsdt(xsdt_t *_xsdt, char *signature);
 Public rsdp_desc_t *acpi_search_rsdp(phys_addr *base,phys_addr *end);
 Public sdt_header_t *acpi_getsdt(char *sig);
 Public uint32 bytesum(phys_addr *base, size_t size);
 Public uint8 acpi_poweroff();
 Public uint8 acpi_enable();
 
 Public rsdp_desc_t *rsdp;
 Public xsdt_t *xsdt;
 Public sdtlst_t sdtlst;
 Public facp_t *facp;
 
 Public sdt_header_t *mcfg_pci;
#endif
