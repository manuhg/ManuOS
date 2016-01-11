#ifndef memory_pae_h
#define memory_pae_h

 #include <types.h>
 #include <access.h>
 #include <kernel/rwregs.h>
 /*
 #ifdef internal
  #undef internal
  #include "memory.h"
  #define internal
 #else
  #include "memory.h"
 #endif*/
 
 #define pae_pdpt_size (4*8)
 #define pae_page_dir (512*8)
 Public void mem_pae_paging_init(); 
 extern void enable_pae_paging(uint32 pdpt_addr);
 extern uint32 set_pg_bit();
 extern uint32 set_pae_bit();
 extern uint32 set_lme_bit();
 extern uint32 set_nxe_bit();
#endif
