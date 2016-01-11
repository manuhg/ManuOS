#include <types.h>
#include <ui_funcs.h> 
#include <drivers/kbd.h>
#define internal
#include "kbd_libfuncs.h"

uint8 kbhit()
{
	keyhit=0;
	while(!keyhit);
	return 1;
}
uint8 kbhit_ascii()
{
	keyhit_ascii=0;
	kbhit();
	if(keyhit_ascii)
	 return 1;
	else
	 return 0;
}
char getch()
{
	while(1)
	{
		if(kbd_status.kbuf<=kbd_status.kbuf_end)
		{
			if(*kbd_status.kbuf)
			 return *kbd_status.kbuf--;
		 }
	 }
}

char getche()
{
	while(1)
	{
		if(kbd_status.kbuf<=kbd_status.kbuf_end)
		{
			if(*kbd_status.kbuf)
			{
				outbyte(*kbd_status.kbuf);
				return *kbd_status.kbuf--;
			}
		 }
	 }
}

char *gets(char *a)
{
	char c,*cpy;
	cpy=a;
	while(1)
	{
		c=getche();
		if(c!='\n')
		 *a=c;
		else
		 break;
		a++;
	}
	*a--=0;
	return cpy;	
}

char *gets_(char *a)
{
	char *cpy,*c;uint16 st_pos,end_pos;
	cpy=a;c=a;
	st_pos=get_cursor_pos();
	gets(a);
	end_pos=get_cursor_pos()-2;
	while(st_pos<=end_pos /*&& *c*/)
	{
		*c++=read_screen(st_pos);
		st_pos+=2;
	}
	return cpy;	
}
