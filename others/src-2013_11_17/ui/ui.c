#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <kernel/acpi.h>
#include <apps/apps.h>
#include <apps/app_list.h>
#include <drivers/kbd.h>
#define internal
#include "ui.h"

void ui_screen_init()
{
	_cls(screen_bcg_colour);
	vidram=(uchar *)vdu_mem;
	kbd_off(1);
}

void ui_init()
{
	kbd_set_leds(_NumL_val);
	load_apps();	
}
void ui_main()
{
	char command[80]; int i=0;
	_cls(welcome_scr_bcg);//clear the screen
	welcome(100);// display welcome screen
	_cls(screen_bcg_colour);
	print_manuos();
	kbd_on(1);
	draw_window(0,3,1,4,0x2);
	while(1)
	{
		for(i=0;i<80;i++)
		 command[i]=0;		
		terminal();		
		gets(command);
		if(call_app(command)==error)
		  printf("%s Command not found",command);
	 }	
}

void ui_kbd_input(uint8 k)
{
	if(k){}
}
char *find_space(char *str)
{
	while(*str &&*str!=' ')
	str++;
	return str;
}
char *get_nextword(char *str)
{
	while(*str==' ')
	 str++;
	 return str;
}

void ui_select_line(uint16 y,uint16 colour,uint8 stx,uint8 endx)
{
	draw_window(stx,y,endx,y,colour);
}
void ui_draw_box(uint16 x,uint16 y,uint8 width,uint8 height,uint8 c)
{
	uint16 i,pos;
		
	pos=get_cursor_pos()/2;
	set_cursor_pos(to_offset(x,y)/2);
	for(i=0;i<width+x;i++)
	 outbyte(c);
	set_cursor_pos(to_offset(x,y)/2);
	move_cursor(80*height);
	for(i=0;i<width+x;i++)
	 outbyte(c);
	outbyte(c);
	set_cursor_pos(to_offset(x,y)/2);
	for(i=0;i<height;i++)
	{
		outbyte(c);move_cursor(width-1);outbyte(c);
		outbyte('\n');
	}
	set_cursor_pos(pos);
}


/***********************************************************************
+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
***********************************************************************/
#ifdef ui_txtmode

#ifdef _welcome
void welcome(int millisecs)
{
	draw_window(40,7,120,17,window_colour);	
	move_cursor((screen_size/4)-(strlen(name)/2));
	mprintf(window_colour,"%s\n",name);
	//set_cursor_pos(0);
	update_cursor(81*25*2);
	//if(linear_dots(".",millisecs)){}
	if(millisecs){}
	milliDelay(millisecs);
	set_cursor_pos(0);
}
int linear_dots(char *a,int millisecs)
{
	int pos,distance,duration;
	distance=1;duration=(20*millisecs)/100;//20% of total time
	pos=get_cursor_pos()/2;
	mprintf(dots_colour_1,".  .  .  .  .");	
	set_cursor_pos(0);
	
	while(1)
	{
		set_cursor_pos(pos);		
		
		mprintf(dots_colour_2,a);update_cursor(0);
		milliDelay(duration);millisecs-=duration; 
		mprintf(dots_colour_1,bkspace);
		mprintf(dots_colour_1,a);move_cursor(distance);
		if(!millisecs)
		  return 0;		
		
		move_cursor(distance);
		mprintf(dots_colour_2,a);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(dots_colour_1,bkspace);
		mprintf(dots_colour_1,a);move_cursor(distance);
		if(!millisecs)
		  return 0;
		
		move_cursor(distance);
		mprintf(dots_colour_2,a);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(dots_colour_1,bkspace);
		mprintf(dots_colour_1,a);move_cursor(distance);
		if(!millisecs)
		  return 0;
		
		move_cursor(distance);
		mprintf(dots_colour_2,a);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(dots_colour_1,bkspace);
		mprintf(dots_colour_1,a);move_cursor(distance);
		if(!millisecs)
		  return 0;
		 
		move_cursor(distance);
		mprintf(dots_colour_2,a);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(dots_colour_1,bkspace);
		mprintf(dots_colour_1,a);move_cursor(distance);
		if(!millisecs)
		  return 0;
	  }
	
	return 0;
}
#endif
#ifdef ui_funcs
void terminal()
{
	mprintf(_colour(_brt_yellow,_black),"\n User@ManuOS /root/>");
	//locked_text=get_cursor_pos();
}
void print_manuos()
{
	uint16 a,p;
	p=get_cursor_pos();
	vidram=(uint8 *)vdu_mem;
	for(a=0;a<160;a+=2)
	{
		*vidram++=32;
		*vidram++=(uint8)screen_bcg_colour;
	}
	set_cursor_pos(37);
	mprintf(special_text_colour,name);
	outbyte('\n');
	set_cursor_pos(p/2);
}

#endif
#endif
