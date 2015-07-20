#ifndef ui_funcs_h
#define ui_funcs_h
 #include <access.h>
 #include <portio.h>
 Public void update_cursor(uint16 position);
 Public void move_cursor(int distance);
 Public int get_cursor_pos();
 Public void set_cursor_pos(int offset);
 Public int hide_cursor();

 Public int cls();
 Public void _cls(uint8 colour);
 Public void draw_window(int startx,int starty,int endx,int endy,int colour);
 Public void set_text_colour(int colour, int from,int to);

 Public void clean_line(uint16 offset);
 Public void scroll_up(uint16 lines, uint16 pos, uint16 diff);
 Public void scroll_one_line_down();
 Public void scroll_down(uint8 lines);

 Public char read_screen(uint16 offset);
 Public int outbyte(uint8 c);
 Public int outpix_pos(int c,int colour,int offset);
 Public void _outc_bcg_pos(int colour, int offset);
 Public void _mprintf(char *fmt,int colour);
 Public void _printf(char *fmt);
 Public void print_error(const char *fmt,...);

 #define putc(char_c) outbyte(char_c);
#endif
