#ifndef app_list_h
#define app_list_h
#include <access.h>
 typedef int (*pgm)();
 Public int load_apps();
 Public int call_app(char *app_name);
 Public void include_app(pgm a);
 Public int help();

#endif
