#include <stdio.h>
#include <kernel/cpu.h>
#include <kernel/pci.h>
#include <kernel/interrupts.h>
#include <kernel/memory.h>
#include <kernel/timer.h>
#include <drivers/kbd.h>
#include <drivers/mouse.h>
#include <drivers/ata.h>
#include <ui/ui.h>


#define internal
#include "kernel.h"

void kernel_main() 
{
	_cli();kbd_set_leds(0);
	ui_screen_init();
	init_hardware();
	//while(getch()!='\n');
	ui_main();
	mprintf(error_text_colour,"\n User Interface Manager Exit\nSystem is halting");
	while(1);
}
void init_hardware()
{
	init_gdt();
	init_idt();
	init_devices();
	ui_init();
}

void init_devices()
{
	mem_init();
	timer_pic_init(timer_freq);
	cpu_init();
	pci_init();	
	kbd_init();//init_mouse();	
	_sti();
	ata_init();	
}

void print_multiboot(multiboot_info_t *m)
{
	#ifdef enable_proceedings
	uint64 total=(m->mem_lower*1024)+(m->mem_upper*1024);	
	mem_size=total;
	mprintf(special_text_colour,"\n\t Total memory = ");
	printf("%d bytes %d Kb %d Mb %d Gb",total,(total/1024),(total/1024/1024),(total/1024/1024/1024));
	printf("\n\t Pages actually present = %d",(total/0x1000));
	#else
	if(m->mem_upper){}
	#endif
}
#ifndef _nsound
void start_beep()
{
	out(0x61,3);
}
void stop_beep()
{
	out(0x61,0);
} 
void play_sound(uint32 nFrequence)
{
	uint32 Div;
 	uint8 tmp;
 	Div = 1193180 / nFrequence;
 	out(0x43, 0xb6);
 	out(0x42, (uint8) (Div) );
 	out(0x42, (uint8) (Div >> 8));
 	tmp = in(0x61);
  	if(tmp!=(tmp|3))
  	  out(0x61,tmp|3);
 }
void nosound()
{
	uint8 tmp=(inb(0x61)&0xFC); 
 	out(0x61,tmp);
}
void beep()
{
	play_sound(1000);
	milliDelay(10);
	nosound();
}
#endif
