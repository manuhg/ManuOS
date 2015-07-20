#include <stdio.h>
#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <kernel/cpu.h>
#include <kernel/rwregs.h>
#define internal
#define _32bit_platform
#include "memory.h"

uint64_t page_dir_ptr_tab[4] __attribute__((aligned(0x20)));
uint64_t page_dir[512] __attribute__((aligned(0x1000)));
uint64_t page_tab[512] __attribute__((aligned(0x1000)));
uint64 mem_size=0;

void mem_init()
{
	_printf("\n\t Initialising memory manager and paging ");
	endofkernel=(uint32)&endofkernel;
	mem_size=mem_findsize();
	printf("memsize : %d",(uint32)mem_size);
	mem_paging_init();
	print_multiboot(mbd);
}
uint64 mem_findsize()
{
	uint64 total;
	total=(mbd->mem_lower*1024)+(mbd->mem_upper*1024);
    return total;
}
extern void enable_pae_paging();
void mem_paging_init()
{
	    uint32 i, address = 0;
	    page_dir_ptr_tab[0] = (uint64_t) _ptr_conv &page_dir | 1; // set the page directory into the PDPT and mark it present
	    page_dir[0] = (uint64_t) _ptr_conv &page_tab | 3; //set the page table into the PD and mark it present/writable
	    
	    for(i=0;i<512;i++)
	    {
			page_tab[i] = address | 3; // map address and mark it present/writable
			address = address + 0x1000;
		}
		page_dir[511] = page_dir_ptr_tab[3]; // map pd to itself
		page_dir[510] = page_dir_ptr_tab[2]; // map pd3 to it
		page_dir[509] = page_dir_ptr_tab[1]; // map pd2 to it
		page_dir[508] = page_dir_ptr_tab[0]; // map pd1 to it
		page_dir[507] = (uint64_t)_ptr_conv &page_dir_ptr_tab; // map the PDPT to the directory
		enable_pae_paging();
		
		asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // set bit5 in CR4 to enable PAE
		asm volatile ("movl %%eax, %%cr3" :: "a" (page_dir_ptr_tab)); // load PDPT into CR3
		asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
		mprintf(special_text_colour,"\n\t Paging Enabled ");
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
