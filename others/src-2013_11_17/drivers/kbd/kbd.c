#include <defines.h>
#include <typedefs.h>
#include <functions.h>
#include <ui_funcs.h>
#include <ui/ui.h>
#include <kernel/kernel.h>
#include <kernel/interrupts.h>
#define internal
#include "kbd.h"
#include "kbdlayout.h"
#include "kbd_lyts/us_qwerty.h"

uint8 led_status=0;
uint8 kbd_on_=false;
void kbd_init()
{
	kbd_on(0);	
	kbdstatus_init();
	set_irq_handler(1,irq1_keyb);
}
void kbd_off(uint8 val)
{
	kbd_on_=0;
	if(val)
	 kbd_status_empty();
}
void kbd_on(uint8 val)
{
	kbd_on_=1;
	if(val)
	 kbd_status_empty();
}

void irq1_keyb(regs_t *regs)
{
	uint16 scancode; char c=0;
	scancode = inw(0x60);
	if(kbd_on_)
	{
		if (scancode & 0x80)
		{
			special_keys(scancode);
			//mprintf(bkspace,screen_bcg_colour);
		}
		else
		{
			keyhit=1;
			if(lyt[scancode]>0)
			{
				keyhit_ascii=1;
				if(kbd_status.kbuf<=kbd_status.kbuf_end)
				{
					c=lyt[scancode];
					if(kbd_status.caps+kbd_status.shift==1){if(c>='a'&&c<='z')c-=32;}					
					*(++kbd_status.kbuf)=c;
					
				}
				else
				  {
					  _printf("keyboard buffer full: emptying the buffer");
					  kbdbuf_empty();
					  *(++kbd_status.kbuf)=lyt[scancode];
					  
				  }
			}
			else
			{
				if((-1*lyt[scancode])>39) //non printable
				 ;//mprintf(non_printable[(-1*lyt[scancode])-40],screen_bcg_colour);
				else
				 kbd_handle_scancode(scancode);
			}
		}
	}

	if(regs->int_no){}
}

void kbdstatus_init()
{
	kbd_status.kbuf_start=(char *)(kbd_status.kbd_buffer);
	kbd_status.kbuf_end=(char *)(kbd_status.kbd_buffer+31);
	kbd_status.alt=0;
	kbd_status.caps=0;
	kbd_status.ctrl=0;
	kbd_status.shift=0;
	kbd_status.kbuf=kbd_status.kbuf_start;
	*kbd_status.kbuf=0;
}
void kbdbuf_empty()
{
	kbd_status.kbuf=kbd_status.kbuf_start;
}
void kbd_status_empty()
{
	kbd_status.kbuf_start=(char *)(kbd_status.kbd_buffer);
	kbd_status.kbuf_end=(char *)(kbd_status.kbd_buffer+31);
	kbd_status.alt=0;
	kbd_status.caps=0;
	kbd_status.ctrl=0;
	kbd_status.shift=0;
	kbd_status.kbuf=kbd_status.kbuf_start;
	*kbd_status.kbuf=0;
}
uint8 kbd_set_leds(uint8 bytes)
{
	led_status=led_status^bytes;
	kbd_status.caps=led_status>>2;
	kbd_write(_KbdLed_cmd,_KbdRW);//send command
	kbd_write(led_status,_KbdRW);//send bytes
	return 0;
}

uint8 kbd_scancode_set(uint8 sc_set)
{
	kbd_write(_KbdSc_code_cmd,_KbdRW);
	kbd_write(sc_set,_KbdRW);	
	return 0;
}

void special_keys(uint8 scancode)
{
	if(scancode==0xB6 || scancode==0xAA)kbd_status.shift=0;
}
void kbd_handle_scancode(uint8 scancode)
{
	switch(lyt[scancode])
	{
		case _LShift:
		case _RShift:
		{
			kbd_status.shift=1;
			break;
		}
		case _Bkspace:
		{
			*(++kbd_status.kbuf)='\b';
			break;
		}
		case _Tab:
		{
			*(++kbd_status.kbuf)='\t';
			break;
		}
		case _Enter:
		{
			*(++kbd_status.kbuf)='\n';
		}
		case _CapsL:
		{
			kbd_set_leds(_CapsL_val);
			break;
		}
		case _NumL:
		{
			kbd_set_leds(_NumL_val);
			break;
		}
		case _ScrlL:
		{
			kbd_set_leds(_ScrlL_val);
			break;
		}
		case _Home:
		{
			set_cursor_pos(0);
			break;
		}
		case _End:
		{
			set_cursor_pos(to_offset(0,24));
			break;
		}
		case _Delete:
		{
			memcpy(vidram+2,vidram+4,(screen_size-get_cursor_pos()-1) );			
			break;
		}
		case _Arr_up:
		{
			move_cursor(-80);			
			break;
		}
		case _Arr_down:
		{
			move_cursor(80);			
			break;
		}
		case _Arr_left:
		{
			move_cursor(-1);			
			break;
		}
		case _Arr_right:
		{
			move_cursor(1);			
			break;
		}		
		default :
		break;
	}
}


void kbd_io_wait()
{
	uint8 a; 
	do
	{
		a=inb(_KbdCommand);
	}while(a&2);
	
}
char kbd_write(uint8 bytes, uint16 port)
{
	kbd_io_wait();
	outb(port,bytes);
	if(inb(port)==_KbdAck)
	  return 1;
	else if(inb(port)==_KbdResend)
	  return kbd_cmd_resend(port,port,bytes);
	return 0;
}
uint8 kbd_read(uint16 port)
{
	while(!(inb(_KbdCommand)&1)) ;//wait till output buffer is full
	 return inb(port);
}

char kbd_cmd_resend(uint16 inport,uint16 outport,uint8 data)
{
	kbd_io_wait();
	outb(outport,data);// make maximum of 3 tries
	if(inb(inport)==_KbdAck)
	  return 1;
	else if(inb(inport)==_KbdResend)
	 {
		 kbd_io_wait();
		 outb(outport,data);
	 }
	if(inb(inport)==_KbdAck)
	  return 1;
	else if(inb(inport)==_KbdResend)
	 {
		 kbd_io_wait();
		 outb(outport,data);
	 }	
	if(inb(inport)==_KbdAck)
	  return 1;
	return 0;	
}

