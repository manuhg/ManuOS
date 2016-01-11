#ifndef app_h
#define app_h
#include <access.h>

 #define date_len 50
typedef struct date_info_s{int d,m,y,total;}date_info;

date_info Age(char *bdate, char *tdate);// to find the age
date_info timediff(date_info b,date_info t);

 Public int sc_dl();
 Public int numl();
 Public int capsl();
 Public int scrll();
 Public int Age_main();
 Public int cls_pmos();
 Public int calculator();
 Public int cursor_pos();
 Public int ata_read_print();
 Public int optd();
 Public void ui_events_viewer();
 Public int cpureset();
 
 Private int calc_days(int aaa);
 Private void make_total(date_info *aa);
 Private void fill_date_info(char *date,date_info *a);
 Private int no_leaps(int year);
#endif
