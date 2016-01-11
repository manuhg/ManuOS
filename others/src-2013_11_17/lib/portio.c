#define internal
#include "portio.h"

uint8 inb(uint16 _port)
{
	uchar result;
	__asm__  ("in %%dx, %%al" : "=a" (result) : "d" (_port));
	return result;
}
uint16 inw(uint16 _port)
{
	uint16 result;
	__asm__  ("in %%dx, %%al" : "=a" (result) : "d" (_port));
	return result;
}

uint32 inl(uint16 _port)
{
	uint32 result;
	__asm__  ("inl %%dx,%%eax" : "=a" (result) : "d" (_port));
	return result;
	
}
void outb(uint16 _port, uchar _data)
{
	 __asm__ ("out %%al, %%dx" : :"a" (_data), "d" (_port));
}
void outw(uint16 _port, uint16 _data)
{
	 __asm__ ("out %%al, %%dx" : :"a" (_data), "d" (_port));
}
void outl(uint16 _port, uint32 _data)
{
	  __asm__ ("outl %%eax, %%dx" : :"a" (_data), "d" (_port));
}


