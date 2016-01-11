#ifndef keyboard_h
#define keyboard_h


#include <access.h>
#include <typedefs.h>

#define _KbdCommand 0x64
#define _KbdRW 0x60
#define _KbdLed_cmd 0xED
#define _KbdSc_code_cmd 0xF0
#define _KbdAck 0xFA
#define _KbdResend 0xFE
#define _CapsL_val 4
#define _NumL_val 2
#define _ScrlL_val 1

typedef struct kbd_status_s
{
	char kbd_buffer[32],*kbuf;//value containers
	uint8 alt : 1,shift : 1,ctrl : 1,caps : 1;
	char *kbuf_start,*kbuf_end;//pointers
}kbd_status_t;

 typedef struct key_press{
	 unsigned char col : 5;
	 unsigned char row : 3;
	 unsigned char shift : 1;
	 unsigned char caps : 1;
 }__attribute__((packed)) key_press; 
 
 #define kbd_led_NumLock() kbd_set_leds(_NumL_val)
 #define kbd_led_CapsLock() kbd_set_leds(_CapsL_val)
 #define kbd_led_ScrlLock() kbd_set_leds(_ScrlL_val)
 Public void reset_cpu();
 
 Public void kbd_init();
 Public void irq1_keyb(regs_t *regs);
 Public void kbd_off(uint8 val);
 Public void kbd_on(uint8 val);
 
 Public void kbdbuf_empty();
 Public void kbdstatus_init();
 Public void kbd_status_empty();
 
 Public void kbd_handle_scancode(uint8 scancode);
 Public void special_keys(uint8 scancode);
 Public uint8 kbd_set_leds(uint8 bytes);
 Public uint8 kbd_scancode_set(uint8 sc_set);

 Public void kbd_io_wait();
 Public char kbd_write(uint8 bytes, uint16 port);
 Public uint8 kbd_read(uint16 port);
 Public char kbd_cmd_resend(uint16 inport,uint16 outport,uint8 data);
 Public uint8 keyhit,keyhit_ascii;
 Public kbd_status_t kbd_status;
#endif
