#ifndef mem_libfuncs_h
#define mem_libfuncs_h
#include <types.h>
#include <access.h>
  Public void *memset(void *s,int val,size_t size);
  Public void *memcpy(void *dest,const void *src,size_t count);
  Public uint16 *memsetw(uint16 *dest, uint16 val, size_t count); 
  #ifdef _mem_alloc
   Public uint32 *mem_find_free_mem(size_t size);
   Public void *mem_allocate_mem(uint32 base, size_t size);
   Public void *mem_malloc(size_t size);
  #endif
#endif
