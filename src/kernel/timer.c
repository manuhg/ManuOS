#include <stdio.h>
#define _part_of_kernel
#include <ui/ui.h>
#include <kernel/kernel.h>
#include <kernel/interrupts.h>
#define internal
#include "timer.h"
Public uint64 timer_ticks;
void timer_pic_handler(regs_t *regs)
{
	timer_ticks++;	
	if(regs->int_no==0)
	{}	
}

void timer_pic_init(uint32 frequency)
{	
	uint32 divisor; uint8 l,h;
	set_irq_handler(0,timer_pic_handler);
	divisor=1193180/frequency;
	outb(0x43,0x36);	
	l=(uint8)(divisor&0xFF);
	h=(uint8)((divisor>>8)&0xFF);
	outb(0x40,l);
	outb(0x40,h);
}

int secDelay(unsigned int secs)
{
	uint64 ticks;	
	ticks=timer_secs((int)timer_ticks);
	while(((timer_secs((int)timer_ticks))-ticks)<secs);
	return 0;
}
void milliDelay(unsigned long millisecs)
{
	uint64 ticks;	
	ticks=timer_ticks;
	while((timer_ticks-ticks)<millisecs);
}
