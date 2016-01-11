#ifndef kernel_h
#define kernel_h
#include <access.h>
#include <defines.h>
#include <typedefs.h>
#include <string.h>
#include <portio.h>
#include "multiboot.h"

#define timer_freq 100

#ifndef _nsound
 Public void stop_beep();
 Public void start_beep();
 Public void beep();
 Public void play_sound(uint32 nFrequence);
 Public void nosound();
#endif
 Public void print_multiboot(multiboot_info_t *m);
 Private void init_hardware();
 Private void init_devices();
 
 Public uint32 endofkernel;
 extern uint32 magic;
 extern uint32 stkern;
 extern uint32 startofkernel;
 Public multiboot_info_t *mbd;

#endif
