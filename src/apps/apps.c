#include <kernel/timer.h>
#include <stdio.h>
#include <drivers/kbd.h>
#include <kernel/acpi.h>
#include <ui/ui.h>
#define internal
#include "apps.h"

int optd()
{
	uint8 a=0,select=1,k;uint16 pos1,pos2;
	char *str[2]={"Events viewer","Terminal"};
	a=_colour(_black,_green);
	while(1)
	{
		_cls(a);
		move_cursor((screen_size/4)-(strlen(str[1])/2));outbyte('\r');
		move_cursor(-320);mprintf(a,"\t\t\t");
		mprintf(a,str[0]);move_cursor(80-strlen(str[0]));
		mprintf(a,str[1]);move_cursor(80-strlen(str[1]));
		ui_select_line(8+select,_colour(_green,_black),0,100);
		ui_draw_box(0,6,50,10,219);
		move_cursor(-80*4);
		while(1)
		{
			k=0;
			pos1=get_cursor_pos();
			if(kbhit_ascii())
			  k=getch();
			pos2=get_cursor_pos();		
			if(k)
			{
				switch(select)
				{
					case 0:ui_events_viewer();break;
					case 1:return 0;
				 }
			 }
			 else if(k==0)
			 {
				 if(pos2>pos1 || pos2<pos1)
				  select=select^1;
				 if(pos2>pos1 || pos2<pos1)
				  break;
			 }
			 
		 }
		
	}
	return 0;
}
void ui_events_viewer()
{
	char *text1={" SORRY THERE IS NOTHING HERE :P "};
	char *text2={" I MADE IT SIMPLY JUST TO GIVE MORE THAN 1 OPTION IN THE PREVIOUS MENU ;P"};
	cls();
	print_manuos();
	outbyte('\n');
	mprintf(special_text_colour,"Evnets viwer:");
	move_cursor((screen_size/4)-(strlen(text1)/2)-80);
	mprintf(error_text_colour,text1);
	_printf("\n\r");
	move_cursor(3);
	_printf(text2);
	_printf("\n\n\n\n\npress k to return to menu : ");
	while(getch()!='k');	
}

int cpureset()
{
	_cli();
	kbd_write(0xfe,0x64);
	return 0;
}

int poweroff()
{
	acpi_poweroff();
	return 0;
}

int Age_main()
{
	char bdate[date_len],tdate[date_len],c; boolean again;
	date_info a;
	again=true;
	_printf("\nWelcome to Age finder program written in C\n");
	while(again) 
	{
		_printf("================================================================================\n");
		_printf("Enter Birth date: ");
		gets_(bdate);
		_printf("Enter Todays date: ");
		gets_(tdate);
		a=Age(bdate,tdate);//find the age
		_printf("\nYour age is: ");
		_print_int(a.total);
		_printf(" (in terms of days)\n\t");
		_print_int(a.y);
		_printf(" years\n\t");
		_print_int(a.m);
		_printf(" months\n\t");
		_print_int(a.d);
		_printf(" days");
		_printf("\n\nDo you want to calculate age again? y/n\r");
		c=getch();
		if(c=='y' || c=='Y')
		{
			again=true;
			_printf("Do you want to clear the contents of screen? y/n\r");
			c=getch();
			if(c=='y' || c=='Y')
				{
					cls_pmos();
					_printf("\nAge finder program written in C\n");
			    }
		}
		else
			again=false;
	}
	thanks();// print thank you manu hegde......... on screen and wait for a key on keyboard to be pressed.
	return 0;
}

int cursor_pos()
{
	_print_int(get_cursor_pos());
	return 0;
}

int ata_read_print()
{/*
	char buffer[512];
	read_ata_disk(1,(uint32)buffer,0,1);*/
	_printf("\nATA Read is not functional as of now.");
	return 0;
}

int sc_dl()
{
	secDelay(1);
	return 0;
}
int numl()
{
	kbd_led_NumLock();
	return 0;
}
int capsl()
{
	kbd_led_CapsLock();
	return 0;
}
int scrll()
{
	kbd_led_ScrlLock();
	return 0;
}
int cls_pmos()
{
	cls();
	print_manuos();
	return 0;
}
int calculator()
{
	char eqtn[100];
	_printf("\nCalculator:");
	gets(eqtn);
	return 0;
}

date_info Age(char *bdate, char *tdate) 
{
	
	date_info a,b,t;

	fill_date_info(bdate,&b);
	fill_date_info(tdate,&t);
	a=timediff(b,t);
	/*make_total(&b);
	make_total(&t);

	a.total=t.total-b.total;//a.total= age in terms of days
	a.y=a.total/356;
	a.m=(a.total%356)/30;
	a.d=(a.total%356)%30;*/

	return a;
}
date_info timediff(date_info b,date_info t)
{
      int dif=0; date_info r;
      dif=((30*t.m)+t.d)-((30*b.m)+b.d);
      dif+=(t.y-b.y)*360; //12*30=360 bcoz one month is considered as 30 days
      r.total=dif;
      r.y=dif/360;
      r.m=(dif%360)/30;
      r.d=(dif%360)%30;
      return r;
}

int calc_days(int aaa) 
{
	int a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int month,sum,aa,i;
	aa=0;sum=0;i=1;month=1;

	while(i<=aaa)
	{
		for(;aa<month;aa++)
			sum+=a[aa];
		i+=1;month+=1;
	}
	return sum;
}

int no_leaps(int year) 
    {
        int i,a=0;
        for(i=1;i<=year;i++) 
        {
            if(leap(i))
             a+=1;
        }
        return a;
    }

void make_total(date_info *a)
{
	a->total=0;
	a->total+=calc_days(a->m);//if month is april then add number of days till april to the sum
	if(leap(a->y) && a->m>2)
		a->total+=1; //if it is leap year and the month is comes after february, increment total days by 1
	a->total+=a->d;// if birth date is april 8th, add 8 to the sum of days
	a->total+=((a->y-1)*356)+no_leaps(a->y-1);// multiply 356 to 1996 if birth year is 1997 and find how many leap years occur till 1996 and add their numer
}

void fill_date_info(char *date,date_info *a)
{
	a->d=strtoint_mov(&date);//passing address of pointer bdate to pointer of pointer
	++date;
	a->m=strtoint_mov(&date);
	++date;
	a->y=strtoint_mov(&date);
}
