#include <stdio.h>
#define _part_of_kernel
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <kernel/cpu.h>
#include <kernel/rwregs.h>
#define _32bit_platform
#include "memory.h"
#define internal
#include "memory_pae.h"

uint64_t *page_dir_ptr_tab/*[4]*/ __attribute__((aligned(0x20)));
uint64_t *page_dir_pae/*[512]*/ __attribute__((aligned(0x1000)));
uint64_t *page_tab_pae/*[512]*/ __attribute__((aligned(0x1000)));

void mem_pae_paging_init()
{
	    uint32 i, address = 0;uint64_t * page_dir__;
	    page_dir_ptr_tab=(uint64_t *)page_tab+(1024*1024*4)+0x20;
	    page_dir_pae=(uint64_t *)page_dir_ptr_tab+pae_pdpt_size+0x20;
	    page_tab_pae=(uint64_t *)page_dir_pae+pae_page_dir+0x20;	    
	    page_dir_ptr_tab[0] = (uint64_t) _ptr_conv page_dir_pae | 1; // set the page directory into the PDPT and mark it present
	    page_dir_pae[0] = (uint64_t) _ptr_conv page_tab_pae | 3; //set the page table into the PD and mark it present/writable
	    
	    for(i=0;i<512;i++)
	    {
			page_tab_pae[i] = address | 3; // map address and mark it present/writable
			address = address + 0x1000;
		}
		page_dir__ = (uint64_t*)_ptr_conv page_dir_ptr_tab[3]; // get the page directory (you should 'and' the flags away)
		page_dir__[511] = (uint64_t)_ptr_conv page_dir; // map pd to itself
		page_dir__[510] = page_dir_ptr_tab[2]; // map pd3 to it
		page_dir__[509] = page_dir_ptr_tab[1]; // map pd2 to it
		page_dir__[508] = page_dir_ptr_tab[0]; // map pd1 to it
		page_dir__[507] = (uint64_t)_ptr_conv &page_dir_ptr_tab;
		
		printf("\t Address of of pdpt = %d",_ptr_conv&page_dir_ptr_tab);
		//asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // set bit5 in CR4 to enable PAE
		//asm volatile ("movl %%eax, %%cr3" :: "a" (&page_dir_ptr_tab)); // load PDPT into CR3
		//asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
		
		//mprintf(special_text_colour,"\n\t Paging Enabled ");
}
