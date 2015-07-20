#define internal
#include "mem_libfuncs.h"
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

int memcmp(const void *mem1, const void *mem2, size_t size)
{
	int i=0,*ptr1=(int *)mem1,*ptr2=(int *)mem2;
	while(size--)
	{
		i=*ptr1-*ptr2;
		if(i)return i;
	}
	return 0;
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
