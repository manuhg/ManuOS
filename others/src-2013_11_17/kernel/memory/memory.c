#define _kernel_rel
#include <kernel/kernel.h>
#include <kernel/cpu.h>
#define _32bit_platform
#include "memory_pae.h"
#define internal
#include "memory.h"

/**
 * normal page directory can hold upto 4Gb
 * 1 pagetable can hold 4mb if each page is 4kb
 * pagedirectory takes up 4 kb and even 1 page table takes 4 kb
 * 
 * each pdpt entry will point to 1 pagedir
 * uint64 pagetable[4][512][512];
 * uint64 pagedir[4][512];
 * uint64 pdpt[4];
 * uint64 *pagingstruct=pdpt;
 * load cr3 with pagingstruct
 */
mem_node_t *free_mem,*allocated_mem;
phys_addr free_base=0; uint64 mem_size;

uint32 *page_dir __attribute__((aligned(0x1000)));  // must be aligned to page boundary
uint32 *page_tab __attribute__((aligned(0x1000)));

void mem_init()
{
	endofkernel=(uint32)&endofkernel;
	print_multiboot(mbd);
	mem_paging_init();
	if(1)
	{
		mem_pae_paging_init();
	}
}
void mem_alloc_ps(paging_structs_t *p)
{
	phys_addr addr=0;
	addr=endofkernel;
	
	p->dir=(uint64 *) _ptr_conv _aligned_addr(addr,0x1000);
	addr=((uint64) _ptr_conv p->dir)+(4*_1page_dir_size);
	p->tab=(uint64 *) _ptr_conv _aligned_addr(addr,0x1000);
	addr=((uint64) _ptr_conv p->tab)+(4*512*_1page_tab_size);
	p->pdpt=(uint64 *) _ptr_conv  _aligned_addr(addr,0x20);
	
	free_base=_aligned_addr(addr+_1pdpt_size,0x1000);
	
	p->start=p->dir;
	p->end=(phys_addr *) _ptr_conv free_base;
	return;
}
void mem_paging_init()
{
	int i,addr,pages;
	page_dir=(uint32 *) ((endofkernel&0xFFFFF000)+0x1000);
	page_tab=page_dir+0x1000; //decimal equivalent is 32768. pagedir takes up 32kb
	addr=0;
	for(i=0;i<1024;i++)// blank the page directory
	 page_dir[i]=0b10;//decimal equivalent 2	
	pages=(mem_size/4096);
	for(i=0;i<1024*1024;i++)
	{
		page_tab[i]=addr|2;
		addr+=4096;
	}
	addr=0;
	for(i=0;i<pages;i++)
	{
		page_tab[i]=addr|3;
		addr+=4096;
	}
	for(i=0;i<1024;i++)
	{
		page_dir[i]=(uint32)& page_tab[512*i];
		page_dir[i]|=3;
	}	
	asm volatile("mov %0, %%cr3":: "b"(page_dir));
	asm volatile("mov %%cr0, %0": "=b"(i));
	i |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(i));
	mprintf(special_text_colour,"\n\t Paging Enabled ");
	printf("\n\t %d kb or %d Mb has been paged",pages*4,(pages*4)/1024);
}
void mem_map_virt2phys(virt_addr v,phys_addr p)
{
	if(v+p){}
}
void mem_fill_pageT(phys_addr *pagetable,phys_addr *addr,uint16 flags)//maps 1 page table or 1 entry in pagedir
{
	uint16 i;
	for(i=0;i<512;i++)
	{
		if((*addr/4096)>mem_size/4096)
		  flags=(flags>>1)<<1;
		*(pagetable+i)=(*addr|flags);
		*addr+=_page_size;
	}
}
