#ifndef us_qwetry_lyt
#define us_qwetry_lyt

#include <ui/kbd_keycodes.h>

#define keys(high,low) ((high<<8)|low)
#define gkeyhigh(key_val) (key_val>>8)
#define gkeylow(key_val) (key_val&0xff)

#define scancode_set 2

#if scancode_set==1
uint8 lyt_p[]=
{
	Esc,akey1,akey2,akey3,akey4,akey5,akey6,akey7,akey8,akey9,
	akey0,akey_minus,akey_equals,akey_backspace,akey_tab,akeyq,akeyw,akeye,akeyr,akeyt,
	akeyy,akeyu,akeyi,akeyo,akeyp,akey_sqrbro,akey_sqrbrc,akey_enter,LCtrl,akeya,
	akeys,akeyd,akeyf,akeyg,akeyh,akeyj,akeyk,akeyl,akey_semicolon,akey_quotes,
	akey_backtick,LShift,akey_bkslash,akeyz,akeyx,akeyc,akeyv,akeyb,akeyn,akeym,
	akey_comma,akey_dot,akey_slash,RShift,akey_star_nump,LAlt,akey_space,CapsLock,F1,F2,
	F3,F4,F5,F6,F7,F8,F9,F10,NumLock,ScrlLock,
	akey7_nump,akey8_nump,akey9_nump,akey_minus_nump,akey4_nump,akey5_nump,akey6_nump,akey_plus_nump,akey1_nump,0,
	0,0,F11,F12
};

uint8 lyt_s[]=//begins from E0,1C ends at E0,5D
{
	akey_enter/*numpad*/,RCtrl,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,akey_slash_nump,0,0,RAlt,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,Home,ArrUp,PageUp,0,ArrRight,0,End,ArrDown,PageDown,Insert,Delete,
	0,0,0,0,0,0,0,0,LGui,RGui,Apps
};
#ifdef _nfor_ref
#define _KbdCommand 0x64
#define _KbdRW 0x60
#define _KbdLed_cmd 0xED
#define _KbdSc_code_cmd 0xF0
#define _KbdAck 0xFA
#define _KbdResend 0xFE
#define _CapsL_val 4
#define _NumL_val 2
#define _ScrlL_val 1
#define _Bkspace -1
 
#define _Tab -2
#define _Enter -3
#define _CapsL -8
#define _NumL -9
#define _ScrlL -10
#define _Home -23
#define _End -29
#define _Delete -32
#define _Arr_up -24
#define _Arr_down -28
#define _Arr_left -26
#define _Arr_right -27

#define _Pg_up -25
#define _Pg_down -30
#define _Ins -31
#define _LShift -5
#define _RShift -6
#define _Ctrl -48
//#define _LCtrl -4
//#define _RCtrl -4
#define _Alt -49
//#define _LAlt -7
//#define _RAlt -7
#define _F1 -11
#define _F2 -12
#define _F3 -13
#define _F4 -14
#define _F5 -15
#define _F6 -16
#define _F7 -17
#define _F8 -18
#define _F9 -19
#define _F10 -20
#define _F11 -21
#define _F12 -22

char lyt[128] =
{
    -40,  -41, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', -1,	/* Backspace */
  -2,			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', -3,		/* Enter key */
    -48,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   -5,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   -6,					/* Right shift */
  '*',
    -49,	/* Alt */
  ' ',	/* Space bar */
    -8,	/* Caps lock */
    -11,	/* 59 - F1 key ... > */
    -12,  -13,   -14,   -15,   -16,   -17,   -18,   -19,
    -20,	/* < ... F10 */
    -9,	/* 69 - Num lock*/
    -10,	/* Scroll Lock */
    -23,	/* Home */
    -24,	/* Up Arrow */
    -25,	/* Page Up */
  '-',
    -26,	/* Left Arrow */
    -42,
    -27,	/* Right Arrow */
  '+',
    -29,	/* 79 - End*/
    -28,	/* Down Arrow */
    -30,	/* Page Down */
    Insert,	/* Insert */
    Delete,	/* Delete */
    0,0,0,
   F11,	/* F11 */
    F12,	/* F12 */
    -47,	/* All others */
};
#endif
#elif scancode_set==2
uint8 lyt_p[]=
{
	F9,0,F5,F3,F1,F2,F12,0,F10,F8,
	F6,F4,akey_tab,akey_backtick,0,0,RAlt,LShift,0,0,
	LCtrl,akeyq,akey1,0,0,0,akeyz,akeys,akeya,akeyw,
	akey2,0,0,akeyc,akeyx,akeyd,akeye,akey4,akey3,0,
	0,akey_space,akeyv,akeyf,akeyt,akeyr,akey5,0,0,akeyn,
	akeyb,akeyh,akeyg,akeyy,akey6,0,0,0,akeym,akeyj,
	akeyu,akey7,akey8,0,0,akey_comma,akeyk,akeyi,akeyo,akey0,
	akey9,0,0,akey_dot,akey_slash,akeyl,akey_semicolon,akeyp,akey_minus,0,
	0,0,akey_quotes,0,akey_sqrbro,akey_equals,0,0,CapsLock,RShift,
	akey_enter,akey_sqrbrc,0,akey_bkslash,0,0,0,0,0,0,
	0,0,akey_backspace,0,0,akey1_nump,0,akey4_nump,akey7_nump,0,0,0,akey0_nump,
	akey_dot_nump,akey2_nump,akey5_nump,akey6_nump,akey8_nump,Esc,NumLock,F11,akey_plus_nump,akey3_nump,
	akey_minus_nump,akey_star_nump,akey9_nump,ScrlLock,0,0,0,0,F7
};

uint8 lyt_s[]=
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,mm_www_search,RAlt,0,0,RCtrl,
	mm_prev_track,0,0,mm_www_favorites,0,0,0,0,0,0,
	LGui,mm_www_refresh,mm_volume_down,0,mm_volume_mute,0,0,0,RGui,mm_www_stop,
	0,0,mm_calculator,0,0,0,Option,mm_www_forward,0,mm_volume_up,
	0,mm_play_pause,0,0,ACPI_Power,mm_www_back,0,mm_www_home,mm_stop,0,
	0,0,ACPI_Sleep,mm_mycomp,0,0,0,0,0,0,
	0,mm_www_email,0,akey_slash_nump,0,0,mm_next_track,0,0,mm_media_select,
	0,0,0,0,0,0,0,0,0,akey_enter,
	0,0,0,ACPI_WakeUp,0,0,0,0,0,0,
	0,0,0,0,End,0,ArrLeft,Home,0,0,
	0,Insert,Delete,ArrDown,0,ArrRight,ArrUp,0,0,0,
	0,PageDown,0,0,PageUp
};
#endif
//here in bitmap it is assumed that numpad is is not present
/*
uint32 key_bitmap[7]=
{ 0,//no keys in row humber 0 is printable.
  0b111111111111111, //the lowest bit will be telling aboutfirst key in the row
  0b1111111111111,//tab has '\t' hence it has ascii value assigned to it
  0b1111111111110,//Capslock is not printable no ascii value assigned to it
  0b11111111110,//lshift in not printable
  0b1000,// only space is printable. lctrl,alt and lgui ain't printable
  0b0
};*/
uint16 ascii_keys[]=
{
	keys('~','`'),keys('!','1'),keys('@','2'),keys('#','3'),keys('$','4'),
	keys('%','5'),keys('^','6'),keys('&','7'),keys('*','8'),keys('(','9'),
	keys(')','0'),keys('_','-'),keys('+','='),keys('|',92) ,keys('\b','\b'),/**92-backslash*/
	keys('\t','\t'),
	
	keys('{','['),keys('}',']'),keys(':',';'),keys('"',44),/**44-single quote*/	
	keys('<',','),keys('>','.'),keys('?','/'),keys(' ',' '),keys('\n','\n'),
	
	keys('Q','q'),keys('W','w'),keys('E','e'),keys('R','r'),keys('T','t'),
	keys('Y','y'),keys('U','u'),keys('I','i'),keys('O','o'),keys('P','p'),
	keys('A','a'),keys('S','s'),keys('D','d'),keys('F','f'),keys('G','g'),
	keys('H','h'),keys('J','j'),keys('K','k'),keys('L','l'),keys('Z','z'),
	keys('X','x'),keys('C','c'),keys('V','v'),keys('B','b'),keys('N','n'),
	keys('M','m'),
	
};
#endif
