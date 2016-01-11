/*000
100=4-CapL
010=2-NumL
001=1-ScrlL*/
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

#define _Unkk1 -40
#define _Unkk2 -41
#define _Unkk3 -42
#define _Unkk4 -43
#define _Unkk5 -44
#define _Unkk6 -45
#define _Unkk7 -46
#define _Unkk8 -47

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
    -31,	/* Insert */
    -32,	/* Delete */
    -44,   -45,   -46,
    -21,	/* F11 */
    -22,	/* F12 */
    -47,	/* All others */
};

char non_printable[][5] =
{
   "Unkk1", "Unkk2", "Unkk3", "Unkk4",
   "Unkk5", "Unkk6", "Unkk7", "Unkk8",
   "Ctrl ", "Alt  ", 
};

char lyt_sc2[]=
{
 -19/*0x01,F9 p*/, 0/*0x02,unknown*/,
 -15/*0x03,F5 p*/, -14/*0x04,F4 p*/,
 -11/*0x05,F1 p*/, -12/*0x06,F2 p*/,
 -22/*0x07,F12 p*/, 0/*0x08,unknown*/,
 -10/*0x09,F10 p*/, -18/*0x0a,F8 p*/};
 
 
 unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};