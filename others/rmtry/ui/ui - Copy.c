#include <defines.h>
#include <typedefs.h>
#include <stdio.h>
#include <kernel/kernel.h>
#include <kernel/timer.h>
#include <apps/app_list.h>
#include <drivers/kbd.h>
//#include <ui/kbd_keycodes.h>
#define internal
#include "ui.h"
void ui_screen_init()
{
	_cls(screen_bcg_colour);
	timer_ticks=0;
	locked_text=0;
	vidram=(uchar *)vdu_mem;
	print_time=false;
	kbd_on=false;	
}

void ui_init()
{
	load_apps();	
}
void ui_main()
{
	char command[80]; int i;//,app[3],*app_n,*app_n_end,*a;boolean not_found;
	char c;
	
	_cls(welcome_scr_bcg);//clear the screen
	welcome(100);// display welcome screen
	ui_option_display();
	_cls(screen_bcg_colour);
	print_time=true;
	print_manuos();
	kbd_status_empty();
	kbd_on=true;
	while(1)
	{
		i=0;		
		//not_found=true;app_n=(char *)command;a=(char *)app;
		terminal();
		do
		{
			c=getch();
			if(c!='\n')
			{
				outbyte(c);
				if(c=='\b')
				 --i;
				else if(c=='\t')
				 {
					 int j;
					 for(j=i;j<4;j++)
					  command[j]=' ';
				 }
				else 
				 command[i++]=c;
			}
		}while(c!='\n');
		_printf("\nCommand not found");
		//call_app(command);
		continue;
		//gets_(command);
		/*
		mprintf("\nYou typed:",screen_bcg_colour);
		mprintf(command,screen_bcg_colour);
		while(not_found && *app_n)
		{
			if(*app_n!=' ')
			 break;
			else
			 app_n++;
		}
		not_found=true; app_n_end=app_n;
		
		while(not_found && *app_n_end)
		{
			if(*app_n_end==' ')
			 break;
			else
			 app_n_end++;
		}
		while(app_n<=app_n_end)
		{
			*a++=*app_n++;
		}*//**
		if(command[0]=='\n'||command[1]=='\n'||command[2]=='\n')
		 continue;
		else if(call_app(command)==error)
		{
			mprintf(command,screen_bcg_colour);
			mprintf("Command not found",screen_bcg_colour);
		}*/
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

void ui_option_display()
{
	#define _options_bef_ter
	#ifdef _options_bef_ter
	uint8 a=0,select=1; uint8 k;uint16 pos1,pos2;
	char *str[2]={"Events viewer","Terminal"};
	print_time=0;kbd_on=0;
	kbd_off();
	a=_colour(_black,_green);
	while(1)
	{
		_cls(a);
		move_cursor((screen_size/4)-(strlen(str[1])/2));outbyte('\r');
		move_cursor(-320);mprintf("\t\t\t",a);
		mprintf(str[0],a);move_cursor(80-strlen(str[0]));
		mprintf(str[1],a);move_cursor(80-strlen(str[1]));
		ui_select_line(8+select,_colour(_green,_black),0,100);
		ui_draw_box(0,6,50,10,219);
		kbd_on=1;
		while(1)
		{
			k=0;
			hide_cursor();
			pos1=get_cursor_pos();
			if(kbhit_ascii())
			  k=getch();
			pos2=get_cursor_pos();
			hide_cursor();			
			if(k/*=='\n'*/)
			{
				switch(select)
				{
					case 0:ui_events_viewer();goto after_ev_;
					case 1:return;
				 }
			 }
			 else if(k==0)
			 {
				 if(pos2>pos1 || pos2<pos1)
				  select=select^1;
				 if(pos2>pos1 || pos2<pos1)
				  break;
				 /*
				 #define _Arr_up -24
				 #define _Arr_down -28
				 if(k==ArrUp)
				  select=(select>0)?(select-1):select;
				 if(k==ArrDown)
				  select=(select<1)?(select+1):select;
				 if(k==ArrUp || k==ArrDown)
				  break;*/
			 }
			 
		 }
		
	}
	after_ev_:
	secDelay(2);
	cls();
	print_time=1;
	#endif
}
void ui_events_viewer()
{
	cls();
	print_manuos();
	outbyte('\n');
	mprintf("Evnets viwer:",special_text_colour);
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
	mprintf(name "\n"/*\t\t\t\t\t\t\t\t"*/,window_colour);
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
	mprintf(".  .  .  .  .",dots_colour_1);	
	set_cursor_pos(0);
	
	while(1)
	{
		set_cursor_pos(pos);		
		
		mprintf(a,dots_colour_2);update_cursor(0);
		milliDelay(duration);millisecs-=duration; 
		mprintf(bkspace,dots_colour_1);
		mprintf(a,dots_colour_1);move_cursor(distance);
		if(!millisecs)
		  return 0;		
		
		move_cursor(distance);
		mprintf(a,dots_colour_2);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(bkspace,dots_colour_1);
		mprintf(a,dots_colour_1);move_cursor(distance);
		if(!millisecs)
		  return 0;
		
		move_cursor(distance);
		mprintf(a,dots_colour_2);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(bkspace,dots_colour_1);
		mprintf(a,dots_colour_1);move_cursor(distance);
		if(!millisecs)
		  return 0;
		
		move_cursor(distance);
		mprintf(a,dots_colour_2);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(bkspace,dots_colour_1);
		mprintf(a,dots_colour_1);move_cursor(distance);
		if(!millisecs)
		  return 0;
		 
		move_cursor(distance);
		mprintf(a,dots_colour_2);update_cursor(0);
		milliDelay(duration);millisecs-=duration;
		mprintf(bkspace ,dots_colour_1);
		mprintf(a,dots_colour_1);move_cursor(distance);
		if(!millisecs)
		  return 0;
	  }
	
	return 0;
}
#endif
#ifdef ui_funcs
void terminal()
{
	mprintf("\n User@ManuOS /root/>",_colour(_brt_yellow,_black));
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
	mprintf(name,special_text_colour);
	outbyte('\n');
	set_cursor_pos(p/2);
}

#endif
#endif
