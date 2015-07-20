#include <ui/ui.h>
#include <stdio.h>
#define internal
#include "ui_funcs.h"

void clean_line(uint16 offset)
{
	uint16 end;
	end=80-(offset%80);
	while(end--)
	 outbyte(32);
	set_cursor_pos(offset);	
}

void scroll_up(uint16 lines, uint16 pos, uint16 diff) //probably it is supposed to be scroll down function 
{
	int curpos; uint8 *src;
	uint16 a=0;src=(uint8 *)(vdu_mem+pos); 
	curpos=get_cursor_pos();
	set_cursor_pos(pos);
	if(pos<to_offset(0,80))
	{
		src+=diff;
		for(;a<lines*cols;a++)
		  outbyte(*src++);
	}
	else
	{
		for(;a<lines*cols;a++)
		  outbyte(0);
	}
	set_cursor_pos(curpos/2);	
}
void scroll_one_line_down()
{
	int i=0;uint8 *vd_dst=(uint8 *)(vdu_mem);
	memcpy(vd_dst,(uint8 *)(vdu_mem+160),(screen_size-160));
	vd_dst=(uint8 *)(vdu_mem)+to_offset(0,24);
	for(i=0;i<160;i+=2)
	 *(vd_dst+i)=0;
}

void scroll_down(uint8 lines)
{
	uint8 i,*vd_dst;
	while(lines--)
	{
		vd_dst=(uint8 *)(vdu_mem);
		memcpy(vd_dst,(uint8 *)(vdu_mem+160),(screen_size-160));
		vd_dst=(uint8 *)(vdu_mem)+to_offset(0,24);
		for(i=0;i<160;i+=2)
		  *(vd_dst+i)=0;
		//scroll_one_line_down();
	}
	 
}

void print_error(const char *fmt,...)
{
	if(*fmt){}
	//mprintf(error_text_colour,fmt,...);
}
void _mprintf(char *fmt,int colour)
{

	while(*fmt!='\0')
	{
		if((get_cursor_pos()/2)==((80*25*2)-1))
		{
			cls(screen_bcg_colour);
			set_cursor_pos((get_cursor_pos()/2)%80);// shoudnt it be setting to (0,0)
		}
		 
	    outpix_pos(*fmt,colour,get_cursor_pos());
	    	   
	   fmt++;
	}
	
} 
void _printf(char *fmt)
{
	_mprintf(fmt,screen_bcg_colour);
} 
int cls()
{
	int i;
	vidram=(uint8 *)vdu_mem;
	for(i=0;i<=screen_size;i+=2)
	{
		*(vidram+i)=32;
		*(vidram+i+1)=(uint8)screen_bcg_colour;
	}
	return 0;	
}
void _cls(uint8 colour)
{
	int i;
	vidram=(uint8 *)vdu_mem;
	for(i=0;i<=screen_size;i+=2)
	{
		*(vidram+i)=32;
		*(vidram+i+1)=colour;
	}	
}
void update_cursor(uint16 position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8)(position&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8)((position>>8)&0xFF));
}
int get_cursor_pos()
{
	int offset;
	offset=vidram-(uint8 *)vdu_mem;
	return offset;
}
int hide_cursor()
{
	outw(0x3D4,0x200A);
	outw(0x3D4,0xB);
	update_cursor(81*25*2);
	return 0;
}
void move_cursor(int distance)
{
	int offset,tmp;
    vidram+=distance*2;    
    offset=(vidram-(uint8 *)vdu_mem)/2;
    if((uint32)vidram>(vdu_mem+4000))
    {
		tmp=((uint32)vidram-0xB8FA0)/2; //0xB8FA0=0xB8000 + 4000
		scroll_down(((tmp/80)+1));
		print_manuos();
		set_cursor_pos(24*80);
		move_cursor(tmp%80);
		return;
	}
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uchar)(offset&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uchar)((offset>>8)&0xFF));
}
  
void move_cursor_(int distance)
{
	int offset,tmp;
    vidram+=distance*2;    
    offset=(vidram-(uchar *)vdu_mem)/2;
    if((uint32)vidram>=(vdu_mem+4000))
    {
		tmp=((uint32)vidram-(vdu_mem+4000))/2;
		//cls();
		scroll_down(((tmp/80)+1));
		//vidram=(uint8 *)to_offset(0,24)+(tmp%80);
		print_manuos();
	}
     /*
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uchar)(offset&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uchar)((offset>>8)&0xFF));*/
}
void set_cursor_pos(int offset)
{
	vidram=(uint8 *)vdu_mem+(offset*2);
	offset=(vidram-(uint8 *)vdu_mem)/2;
	outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8)(offset&0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8)((offset>>8)&0xFF));
}
void draw_window(int startx,int starty,int endx,int endy,int colour)//startx and starty are co ordinates of top left corner of window endx and endy are the same of bottom right corner
{
	int x;	
	while(starty<=endy)
	{
		for(x=startx;x<=endx;x++)
		 _outc_bcg_pos(colour,to_offset(x,starty));
		starty++;
	 }
		
}
void set_text_colour(int colour, int from,int to)
{
	while(from<=to)
	{
		_outc_bcg_pos(colour,from);
	}
}
int outbyte(uint8 c)
{
	uint16 offset;
	uint8 *vidmem =(uint8 *)vdu_mem;
	
	offset=get_cursor_pos();
	
		if(c=='\r')
		 move_cursor(-1*((offset/2)%80));
		else if(c=='\n')
		 move_cursor(80-((get_cursor_pos()/2)%80));
		
		else if(c=='\b')
		{
			move_cursor(-1);
			outbyte(0);
			move_cursor(-1);
		}
		else if(c=='\t')
		 move_cursor(4);
		else
		{
			move_cursor(1);
			vidmem+=offset;
			*vidmem =c;			
		}
	
	return 0;
}
char read_screen(uint16 offset)
{
	uint8 *a=(uint8 *)vdu_mem;
	a+=offset;
	return *a;
}
int outpix_pos(int c,int colour,int offset)
{
	outbyte(c);
	_outc_bcg_pos(colour,offset);
	return 0;
}
void _outc_bcg_pos(int colour, int offset)//output a colour to the background/ text attribute(not text) at specified position
{
	uint8 *v_mem=(uint8 *)vdu_mem;
	if(offset%2==0)
	   *(v_mem+1+offset)=(uint8)colour;
	else
       *(v_mem+offset)=(uint8)colour;

}
