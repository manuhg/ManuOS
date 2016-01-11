#include <ui_funcs.h>
#include <string.h>
#include <apps/apps.h>
#define internal
#include "app_list.h"

#define no_of_apps (11)
pgm apps[no_of_apps];
char *app_names[]={"age","calc","cls","optd","secdelay","curpos","ataread","capsl","numl","scrll","help","r"};
int a_list_p=0;

int load_apps()
{
	include_app(Age_main);
	include_app(calculator);
	include_app(cls_pmos);
	include_app(optd);
	include_app(sc_dl);
	include_app(cursor_pos);
	include_app(ata_read_print);
	include_app(capsl);
	include_app(numl);
	include_app(scrll);
	include_app(help);
	include_app(cpureset);
	return 0;
}
int call_app(char *app_name)
{
	int i;char called;
	i=0;called=0;
	while(i<no_of_apps)
	{
		if(!strcmp(app_name,app_names[i]))
		  {
			  pgm call_app_=apps[i];
			  return call_app_();
		  }
		  i++;
	}
	if(*app_name){}
	return error;
}
void include_app(pgm a)
{
	apps[a_list_p++]=a;
}

int help()
{
	int i=0;
	while(i<no_of_apps)
	{
		_printf(app_names[i++]);
		_printf("\n");
	}
	return 0;
}
