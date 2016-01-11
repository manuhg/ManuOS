#ifndef memory_h
#define memory_h

 #include <types.h>
 #include <access.h>
 #include <kernel/rwregs.h>
#define _32bit_platform
 typedef uint32 virt_addr;
 typedef uint64 phys_addr;

 typedef struct mem_node_t
{
	 uint64 base;
	 uint16 size;	
	 struct mem_node_t *n; 
} __attribute__((packed)) mem_node_t;

typedef struct paging_structs_s
{
	phys_addr *dir,*tab,*pdpt;
	phys_addr *start,*end;
} __attribute__((packed))paging_structs_t;

 #define _PAE_paging_enable
 #ifdef _32bit_platform
 #define _ptr_conv (uint32)
 #else
 #define _ptr_conv (uint64)
 #endif
 #define _page_size (4096)
 #define _aligned_addr(base,alignment) ((base+alignment)-((base+alignment)%alignment))
 
 #define _1page_dir (512)
 #define _1page_tab (512)
 #define _1pdpt (4)
 #define _total_page_dir (_1page_dir*4)
 #define _total_page_tab (_1page_tab*_1page_tab*4)
 #define _total_pdpt _1pdpt
 #define _1page_dir_size (0x40000*8) /** 0x40000*8=512*512*8bytes */
 #define _1page_tab_size (0x200*8)   /** 0x200*8=512*8bytes */
 #define _1pdpt_size (0x4*8)          /** 4*8bytes */
 
 
 Public void mem_init();
 Public void mem_alloc_ps(paging_structs_t *p);
 Public void mem_paging_init();
 Public void mem_fill_pageT(uint64 *pagetable,uint64 *addr,uint16 flags);
 Public uint64 mem_findsize();
 Public uint64 mem_size;
 Public void mem_map_virt2phys(virt_addr v,phys_addr p);
 
 extern void enable_pae_paging();
#endif
