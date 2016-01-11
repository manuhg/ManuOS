#ifndef defines_h
#define defines_h
#include <types.h>
#include <portio.h>
#define enable_proceedings

#define intel_asm __asm__(".intel_syntax noprefix");
//-masm=intel commandline option if needed to see the c code as assembly in intel syntax
#define fp_seg(fp) (*((unsigned *)&(fp) + 1))
#define fp_off(fp) (*((unsigned *)&(fp)))

#define structconv(ptrtype,struct_) (*(ptrtype *)(&struct_))
#define vartostruct(var,structtype) ((structtype) *((structtype *)(&(var))))

#define low_byte(n) (n & 0x00ff)
#define high_byte(n) ((n>>8)&0x00ff)

#define checkbit(num,pos) (num&(1<<pos))
#define hasbit(var_a,pos) (((var_a&(1<<pos))>0)?1:0)
#define setbit(var_ptr,pos) (var_ptr|=1<<pos)

#define newline "\n"
#define htab "\t"
#define linefeed "\r"
#define bkspace "\b"

#define error (-1)

#define true (1)
#define false (0)

#define sdint_fc "%d"
#define sint_fc  "%i"
#define sint_fc  "%i"
#define uint_fc  "%u"
#define oint_fc "%o"

#define uhex_fc "%x"

#define ushort_fc "%hu"
#define uchar_fc "%hhu"

#define float_fc "%f"
#define double_fc "%lf"
#define ldouble_fc "%Lf"

#define char_fc "%c"
#define str_fc "%s"

#define EXIT_SUCCESS 0

#define hex_len 6
#define bin_fc "%u"
#define sbin_fc "%ld"



/**
00 Black       on Black
01 Blue        on Black
02 Green       on Black
03 Cyan        on Black
04 Red         on Black
05 Magenta     on Black
06 Brown       on Black
07 light Grey        on Black
08 dark Grey        on Black
09 Brt Blue    on Black
0A Brt Green   on Black
0B Brt Cyan    on Black
0C Brt Red     on Black
0D Brt Magenta on Black
0E Brt Yellow  on Black
0F Brt White   on Black
*/
#define _black 0x00
#define _blue 0x01
#define _green 0x02
#define _cyan 0x03
#define _red 0x04
#define _magneta 0x05
#define _brown 0x06
#define _brt_grey 0x07
#define _dark_grey 0x08
#define _brt_blue 0x09
#define _brt_green 0x0A
#define _brt_cyan 0x0B
#define _brt_red 0x0C
#define _brt_magneta 0x0D
#define _brt_yellow 0x0E
#define _brt_white 0x0F

#define _sti() __asm__("sti");
#define _cli() __asm__("cli");

#define _colour(frgd,bckg) ((bckg<<4)|frgd) 


#ifndef _ntext_mode

#define screen_size (80*25*2)
#define screen_bcg_colour _colour(_brt_white,_black)

#define special_text_colour _colour(_green,_black)
#define error_text_colour _colour(_red,_black)
#define success_text_colour _colour(_blue,_black)
#define text_colour screen_bcg_colour

#define line_start(pos) ((pos- (pos%80) ))
#define vdu_mem 0xB8000
#define to_offset(x,y) (y*160+x)

#define null (0)
#define NULL (0)
#define _1sec 1
#define _1min 60
#define _1hour 3600
#define to_bcgoffset(offset) \
 if(offset%2==0)\
  offset+=1; 

    
#define centre_pos(aa,a) ((aa/2)-(a/2))
#define cols 80
#define rows 50
#define _4KB 4096

#endif

#endif
