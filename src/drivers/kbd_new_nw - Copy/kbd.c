#include <ui/ui.h>
#include <stdio.h>
#include <kernel/interrupts.h>
#include <ui/kbd_keycodes.h>
#define internal
#include <drivers/kbd_lyts/us_qwerty.h>
#undef _lib_funcs
#undef _lib_funcs_stdio
#include "kbd.h"

uint8 led_status=0;
uint8 kbd_on_=false;
void kbd_init()
{
	kbd_on(0);	
	kbdstatus_init();
	set_irq_handler(1,irq1_keyb);
}
/*void kbd_init()
{
	//set_irq_handler(1,kbd_irq);	
	int a;
	led_status=_NumL_val;
	kbd_on=true;	
	outbyte(' ');	
	kbd_status_init();
	
	set_irq_handler(1,kbd_irq);
	kbd_set_leds(led_status);
	kbd_scancode_set(scancode_set);	
	kbd_write(0xf0,_KbdRW);
	kbd_write(0x0,_KbdRW);
	a=kbd_read(_KbdRW);
	if(a==_KbdAck)
	{
		a=inw(0x60);
		if(a!=_KbdAck)
		{
			_printf("\n\t Scancode set:");
			_print_int(a);
		}
	}
	kbd_set_leds(led_status);

}*/
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

void kbd_irq(regs_t *regs)
{
	uint16 scancode; keycode_t key;
	scancode = inw(0x60);
	if(kbd_on)
	{
		if((scancode>>8)==0xe0)
		{
			if((scancode&0xff)==0xf0)
			{
				kbd_status.key.make=0;
				// release key for secondary layout keys
			}
			else
			{
				kbd_status.key.make=1;
				//key=vartostruct(lyt_s[scancode&0xff],keycode_t);
				key=(keycode_t)lyt_s[scancode&0xff];
			}
		}
		else if((scancode>>8)==0xf0)
		{
			kbd_status.key.make=0;
			//key=vartostruct(lyt_p[scancode&0xff],keycode_t);	
			key=(keycode_t)lyt_p[scancode&0xff];		
		}
		else
		{
			kbd_status.key.make=1;
			//key=vartostruct(lyt_p[scancode&0xff],keycode_t);
			key=(keycode_t)lyt_p[scancode&0xff];
			if(!key)
			 key=(keycode_t)lyt_s[scancode&0xff];
		}
		kbd_process_key(key);
	}

	if(regs->int_no){}
}
void kbd_irq_v(regs_t *regs,uint16 scancode)
{
	keycode_t key;
	if(kbd_on)
	{
		if((scancode>>8)==0xe0)
		{
			if((scancode&0xff)==0xf0)
			{
				kbd_status.key.make=0;
				// release key for secondary layout keys
			}
			else
			{
				kbd_status.key.make=1;
				//key=vartostruct(lyt_s[scancode&0xff],keycode_t);
				key=lyt_s[scancode&0xff];
			}
		}
		else if((scancode>>8)==0xf0)
		{
			kbd_status.key.make=0;
			//key=vartostruct(lyt_p[scancode&0xff],keycode_t);
			key=lyt_p[scancode&0xff];			
		}
		else
		{
			kbd_status.key.make=1;
			//key=vartostruct(lyt_p[scancode&0xff],keycode_t);
			key=lyt_p[scancode&0xff];
			if(!key)
			 key=lyt_p[scancode&0xff];
		}
		kbd_process_key(key);
		if(kbd_status.kbuf<kbd_status.kbuf_end)
		 *(++kbd_status.kbuf)=kbd_status.key;
		else
		 _printf_error("Keyboard buffuer is full!");
	}

	if(regs->int_no){}
}
uint8 kbd_isprintabke_key(keycode_t key)
{
	if(key>=first_ascii_key || (key>first_numascii&&key<last_numascii))
	 return 1;
	return 0;
}

void kbd_process_key(keycode_t k)//numpad functionality not implemented!
{
	kbd_status.key.key=k;
	if(kbd_isprintabke_key(k))
	{
		if(ascii_keys[k-first_ascii_key])//verify the existance of value in the given position of array
		{
			kbd_status.key.ascii=1;
			if(k>=first_letter_enum && k<=last_letter_enum)//if it a letter, an alphabet
			{
				switch(kbd_status.key.capsl+kbd_status.key.shift)
				{
					case 0:
					{
						kbd_status.key.key=gkeylow(ascii_keys[k-first_ascii_key]);
						break;
					}
					case 1:
					{
						kbd_status.key.key=gkeyhigh(ascii_keys[k-first_ascii_key]);
						break;
					}
					case 2:
					{//same as case 0
						kbd_status.key.key=gkeylow(ascii_keys[k-first_ascii_key]);
						break;
					}
				 }
			  }
			  else //printable but not alphabet
			  {
				  switch(kbd_status.key.shift)
				  {
					  case 0:
					  {
						 kbd_status.key.key=gkeylow(ascii_keys[k-first_ascii_key]);
						  break;
					  }
					  case 1:
					  {
						 kbd_status.key.key=gkeyhigh(ascii_keys[k-first_ascii_key]);
						  break;
					  }
				  }
			  }
		}
	}
	else
	{
		//non printable
		kbd_status.key.ascii=0;
		switch(k)
		{
			case LShift:
			case RShift:
			{
				if(kbd_status.key.make)
				 kbd_status.key.shift=1;
				else
				 kbd_status.key.shift=0;
				return;
			}
			case LAlt:
			case RAlt:
			{
				if(kbd_status.key.make)
				 kbd_status.key.alt=1;
				else
				 kbd_status.key.alt=0;
				return;
			}
			case LCtrl:
			case RCtrl:
			{
				if(kbd_status.key.make)
				 kbd_status.key.ctrl=1;
				else
				 kbd_status.key.ctrl=0;
				return;
			}
			default:
			break;
		}
		if(kbd_status.key.make==0)
		 return;
		switch(k)
		{
			case CapsLock:
			{
				if(led_status&_CapsL_val) //if capslock is already on
				 led_status&=0b11; //turn of capslock
				kbd_set_leds(led_status);
				return;
			}
			case NumLock:
			{
				if(led_status&_NumL_val) //if numlock is already on
				 led_status&=0b101; //turn of numlock
				kbd_set_leds(led_status);
				return;
			}
			case ScrlLock:
			{
				if(led_status&_ScrlL_val) //if scroll lock is already on
				 led_status&=0b110; //turn of scroll lock
				kbd_set_leds(led_status);
				return;
			}
			case Home:
			{
				set_cursor_pos(0);
				return;
			}
			case End:
			{
				set_cursor_pos(to_offset(78,24));
				return;
			}
			case Delete:
			{
				memcpy(vidram+2,vidram+4,(screen_size-get_cursor_pos()-1) );
				//*(vidram+4)=' ';
				//mprintf(bkspace,screen_bcg_colour);
				return;
			}
			case ArrUp:
			{
				move_cursor(-80);
				return;
			}
			case ArrDown:
			{
				move_cursor(80);
				return;
			}
			case ArrLeft:
			{
				move_cursor(-1);
				return;
			}
			case ArrRight:
			{
				move_cursor(1);
				return;
			}
			default:
			 return;
		 }
	}
}

void kbd_status_init()
{
	kbd_status.key.key=0;
	kbd_status.key.ctrl=0;
	kbd_status.key.alt=0;
	kbd_status.key.shift=0;
	kbd_status.key.capsl=0;
	kbd_status.key.numl=0;
	kbd_status.kbuf_start=(kbd_status.kbd_buffer);
	kbd_status.kbuf_end=(kbd_status.kbd_buffer+31);
	kbd_status.kbuf=kbd_status.kbuf_start;
	*kbd_status.kbuf=kbd_status.key;
}
void kbd_buf_empty()
{	
	kbd_status.kbuf_start=(kbd_status.kbd_buffer);
	kbd_status.kbuf_end=(kbd_status.kbd_buffer+31);
	kbd_status.kbuf=kbd_status.kbuf_start;
	*kbd_status.kbuf=kbd_status.key;
}
void kbd_status_empty()
{
	kbd_status.key.key=0;
	kbd_status.key.ctrl=0;
	kbd_status.key.alt=0;
	kbd_status.key.shift=0;
	kbd_status.key.capsl=0;
	kbd_status.key.numl=0;
	kbd_status.key.ascii=0;
	kbd_status.key.numpad=0;
	kbd_buf_empty();
	*kbd_status.kbuf=kbd_status.key;
}
uint8 kbd_set_leds(uint8 bytes)
{
	//led_status|=bytes;
	kbd_write(_KbdLed_cmd,_KbdRW);//send command
	kbd_write(bytes,_KbdRW);//send bytes
	return 0;
}

uint8 kbd_scancode_set(uint8 sc_set)
{
	kbd_write(_KbdSc_code_cmd,_KbdRW);
	kbd_write(sc_set,_KbdRW);	
	return 0;
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
	else if(inb(port)==_KbdResend) // try maximum 3 more times
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

