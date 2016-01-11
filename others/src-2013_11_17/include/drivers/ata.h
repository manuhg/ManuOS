#ifndef ata_h
#define ata_h

#ifndef Private
 #define Private
 #endif
#ifndef Public
 #define Public
 #endif

#ifndef internal
 #ifdef Public
  #undef Public
 #endif
 #define Public extern
#endif

#include <types.h>
 Public void ata_init();
typedef struct ata_pci_dev_s
{
	uint8 bus;
	uint8 dev : 5;
	uint8 func : 3;	 
}ata_pci_dev_t;


#endif
