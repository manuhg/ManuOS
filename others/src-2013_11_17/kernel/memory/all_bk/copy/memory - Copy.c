#define _kernel_rel
#include <kernel/kernel.h>
#include <kernel/cpu.h>
#define internal
#define _32bit_platform
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
phys_addr mem_size=0,free_base=0;

#ifdef _PAE_paging_enable
paging_structs_t page;
#endif
#ifndef _PAE_paging_enable
uint32 *page_dir __attribute__((aligned(0x1000)));  // must be aligned to page boundary
uint32 *page_tab __attribute__((aligned(0x1000)));
#endif
void mem_init()
{
	endofkernel=(uint32)&endofkernel;
	mem_size=mem_findsize();
	_printf("memsize : ");_print_int((uint32)mem_size);
	mem_paging_init();
	print_multiboot(mbd);
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
	#ifdef _PAE_paging_enable
	
		uint8 d,flags=3; uint16 i;
		phys_addr addr=0;		
		mem_alloc_ps(&page);
		for(d=0;d<4;d++)
		{
			for(i=0;i<512;i++)//map 1 directory
			{
				mem_fill_pageT((page.tab+d*512*512+i*512),&addr,flags);//map 1 entry
				*(page.dir+d*512+i)=((uint64)_ptr_conv((page.tab+d*512*512+i*512))|0b11);
			}
		}_printf("\n\t Loading the pdpte to cr3");
		page.pdpt[0]=((uint64)(_ptr_conv&page.dir[0]))| 1;  //present
		page.pdpt[1]=((uint64)(_ptr_conv&page.dir[1]))| 0;  //present
		page.pdpt[2]=((uint64)(_ptr_conv&page.dir[2]))| 0;  //present
		page.pdpt[3]=((uint64)(_ptr_conv&page.dir[3]))| 0;  //present
		asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // set bit5 in CR4 to enable PAE
		asm volatile ("movl %%eax, %%cr3" :: "a" (&page.pdpt)); // load pdpt
		//asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
		
	#endif
	
	#ifndef _PAE_paging_enable
	
		uint32 i,addr;
		page_dir=(uint32 *) ((endofkernel&0xFFFFF000)+0x1000);
		page_tab=page_dir+0x1000; //decimal equivalent is 4096. pagedir takes up 4kb
		addr=0;
		for(i=0;i<1024;i++)// blank the page directory
		  page_dir[i]=0b10;//decimal equivalent 2
		for(i=0;i<1024;i++)
		{
			page_tab[i]=addr|3;
			addr+=4096;
		}
		page_dir[0]=(uint32) page_tab;
		page_dir[0]|=3;
		
		asm volatile("mov %0, %%cr3":: "b"(page_dir));
		asm volatile("mov %%cr0, %0": "=b"(i));
		i |= 0x80000000;
		asm volatile("mov %0, %%cr0":: "b"(i));
	
	#endif
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
uint64 mem_findsize()
{
	uint64 total;
	total=(mbd->mem_lower*1024)+(mbd->mem_upper*1024);
    return total;
}
#ifdef _lib_funcs
void *memset(void *s,int val,size_t size)
{
	char *a=(char *)s;
	while(size--)
	 *a++=val;
	return s;
}

void *memcpy(void *dest,const void *src,size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    while(count--)
     *dp++ = *sp++;
    return dest;
}

uint16 *memsetw(uint16 *dest, uint16 val, size_t count)
{
    uint16 *temp = (uint16 *)dest;
    for( ;count!=0;count--) *temp++=val;
    return dest;
}

#ifdef _mem_alloc
void *mem_malloc(size_t size)
{
	uint32 base;
	base=(uint32)mem_find_free_mem(size);
	if(base)// if any free memory of given size is found
	{
		if(mem_allocate_mem(base,size)) //if allocated successfully
		return ((void *)base);
	}
	return (void *)-1;
}

void *mem_realloc(void *ptr, size_t size)
{
	if(ptr && size){}
	/*
	uint32 base=(uint32)(ptr);
	if(base)
	{
		if(allocate_mem(base,size))
		{
			if(
			return ((void *)base);
		}
	}*/
	return ptr;
}
void *mem_allocate_mem(uint32 base, size_t size)
{
	int i=1; mem_node_t *a=mem_header_lst;
	mem_node_t *prev=mem_header_lst;
	for(i=1;i<=mem_header_lst_len;i++)
	{
		if(a->chunk_base==base)// ah! i found the base where i can allocate memory 
		{
			if((a->chunk_base+size-1)<a->chunk_end)
			 a->chunk_base=a->chunk_base+size;// there is some more free memory left
			else
			{// no more memory left in this chunk of memory, remove the node 
				if(prev!=a)//check if prev and a point to same node or not
				 prev->n=a->n;
				else
				 prev=a->n; //if prev and a point to same node
			}
			return (void *)base;			
		}		
		else// go to next node and see if we can find the base
		{
			prev=a;
			if(a->n)
			 a=a->n;
		}		
	}
	return 0; // sorry, no such memory base addr found :(
}
uint32 *mem_find_free_mem(size_t size)
{
	int i=1; mem_node_t *a=mem_header_lst;
	for(i=1;i<=mem_header_lst_len;i++)
	{
		if((a->chunk_end-a->chunk_base)>=size)						
			return (uint32 *)a->chunk_base;		 
		
		if(a->n)
		 a=a->n;
		else
		 return (uint32 *)0;
	}
	return (uint32 *)0; 
}
#endif
#endif
