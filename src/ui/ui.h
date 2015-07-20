#ifndef ui_h
#define ui_h
 #include <access.h>
 #include <defines.h>
 #include <typedefs.h>
 #include <ui/kbd_keycodes.h>
 #define name "ManuOS"
 #define timer_cur_pos (58)
 #define ui_txtmode

 Public void ui_screen_init();
 Public void ui_init();
 Public void ui_main();
 Public void ui_kbd_input(uint8 k);
 Public char *find_space(char *str);
 Public char *get_nextword(char *str);
 Public void ui_select_line(uint16 y,uint16 colour,uint8 stx,uint8 endx);
 Public void ui_draw_box(uint16 x,uint16 y,uint8 width,uint8 height,uint8 c);
 Public uchar *vidram;

#ifdef ui_txtmode
 #define _welcome
 #define ui_funcs
#endif

#ifdef ui_txtmode
#ifdef _welcome
 #define bckg _brt_grey
 #define welcome_scr_bcg _colour(_black,_black)
 #define window_colour   _colour(_green,bckg)
 #define dots_colour_1   _colour(_brt_grey,bckg)
 #define dots_colour_2   _colour(_red,bckg)
 #define dots_colour     _colour(_red,bckg)
 Private void welcome(int millisecs);
 Public int linear_dots(char *a,int millisecs);
#endif
#ifdef ui_funcs
 Public void print_manuos();
 Public void cmd();
 Private void terminal(); 
#endif
#endif
#endif
