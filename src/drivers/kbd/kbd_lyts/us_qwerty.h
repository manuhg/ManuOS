#define kc(row,col) ((row<<5)|col)
#define _ACPI
#define _Numpad
#define _multimedia
#define col_base 1 //column number starts from 1
#define row_base 1 //row number starts from 1
#define Esc kc((row_base+0),(col_base+0))
#define F1 kc((row_base+0),(col_base+1))
#define F2 kc((row_base+0),(col_base+2))
#define F3 kc((row_base+0),(col_base+3))
#define F4 kc((row_base+0),(col_base+4))
#define F5 kc((row_base+0),(col_base+5))
#define F6 kc((row_base+0),(col_base+6))
#define F7 kc((row_base+0),(col_base+7))
#define F8 kc((row_base+0),(col_base+8))
#define F9 kc((row_base+0),(col_base+9))
#define F10 kc((row_base+0),(col_base+10))
#define F11 kc((row_base+0),(col_base+11))
#define F12 kc((row_base+0),(col_base+12))
#ifdef _ACPI
#define ACPI_Power kc((row_base+0),(col_base+13))
#define ACPI_Sleep kc((row_base+0),(col_base+14))
#define ACPI_WakeUp kc((row_base+0),(col_base+15))
#endif

#define Bkspace kc((row_base+1),(col_base+14))
#define PrintScr kc((row_base+1),(col_base+15))
#define ScrlLock kc((row_base+1),(col_base+16))
#define PauseBrk kc((row_base+1),(col_base+17))

#define Tab kc((row_base+2),(col_base+0))
#define Insert kc((row_base+2),(col_base+13))
#define Home kc((row_base+2),(col_base+14))
#define PageUp kc((row_base+2),(col_base+15))

#define CapsLock kc((row_base+3),(col_base+0))
#define Enter kc((row_base+3),(col_base+12)) //enter key is not considered to be present in 2nd row when Esc is in 0th row
#define Delete kc((row_base+3),(col_base+13))
#define End kc((row_base+3),(col_base+14))
#define PageDown kc((row_base+3),(col_base+15))

#define LShift kc((row_base+4),(col_base+0))
#define RShift kc((row_base+4),(col_base+11))
#define ArrUp kc((row_base+4),(col_base+12))

#define LCtrl kc((row_base+5),(col_base+0))
#define LGui kc((row_base+5),(col_base+1))
#define LAlt kc((row_base+5),(col_base+2))
#define RAlt kc((row_base+5),(col_base+4))
#define RGui kc((row_base+5),(col_base+5))
#define Option kc((row_base+5),(col_base+6))
#define RCtrl kc((row_base+5),(col_base+7))
#define ArrLeft kc((row_base+5),(col_base+8))
#define ArrDown kc((row_base+5),(col_base+9))
#define ArrRight kc((row_base+5),(col_base+10))

// akey means key of prinable char
#define akey_backtick kc((row_base+1),(col_base+0))
#define akey1 kc((row_base+1),(col_base+1))
#define akey2 kc((row_base+1),(col_base+2))
#define akey3 kc((row_base+1),(col_base+3))
#define akey4 kc((row_base+1),(col_base+4))
#define akey5 kc((row_base+1),(col_base+5))
#define akey6 kc((row_base+1),(col_base+6))
#define akey7 kc((row_base+1),(col_base+7))
#define akey8 kc((row_base+1),(col_base+8))
#define akey9 kc((row_base+1),(col_base+9))
#define akey0 kc((row_base+1),(col_base+10))
#define akey_minus kc((row_base+1),(col_base+11))
#define akey_equals kc((row_base+1),(col_base+12))
#define akey_bkslash kc((row_base+1),(col_base+13))

#define akeyq kc((row_base+2),(col_base+1))
#define akeyw kc((row_base+2),(col_base+2))
#define akeye kc((row_base+2),(col_base+3))
#define akeyr kc((row_base+2),(col_base+4))
#define akeyt kc((row_base+2),(col_base+5))
#define akeyy kc((row_base+2),(col_base+6))
#define akeyu kc((row_base+2),(col_base+7))
#define akeyi kc((row_base+2),(col_base+8))
#define akeyo kc((row_base+2),(col_base+9))
#define akeyp kc((row_base+2),(col_base+10))
#define akey_sqrbro kc((row_base+2),(col_base+11))
#define akey_sqrbrc kc((row_base+2),(col_base+12))

#define akeya kc((row_base+3),(col_base+1))
#define akeys kc((row_base+3),(col_base+2))
#define akeyd kc((row_base+3),(col_base+3))
#define akeyf kc((row_base+3),(col_base+4))
#define akeyg kc((row_base+3),(col_base+5))
#define akeyh kc((row_base+3),(col_base+6))
#define akeyj kc((row_base+3),(col_base+7))
#define akeyk kc((row_base+3),(col_base+8))
#define akeyl kc((row_base+3),(col_base+9))
#define akey_semicolon kc((row_base+3),(col_base+10))
#define akey_quotes kc((row_base+3),(col_base+11))

#define akeyz kc((row_base+4),(col_base+1))
#define akeyx kc((row_base+4),(col_base+2))
#define akeyc kc((row_base+4),(col_base+3))
#define akeyv kc((row_base+4),(col_base+4))
#define akeyb kc((row_base+4),(col_base+5))
#define akeyn kc((row_base+4),(col_base+6))
#define akeym kc((row_base+4),(col_base+7))
#define akey_comma kc((row_base+4),(col_base+8))
#define akey_dot kc((row_base+4),(col_base+9))
#define akey_slash kc((row_base+4),(col_base+10))

#define akey_space  kc((row_base+5),(col_base+3))

#ifdef _Numpad
#define NumLock kc((row_base+1),(col_base+18))
#define NumEnter kc((row_base+5),(col_base+13))
#define akey_slash_nump kc((row_base+1),(col_base+19))
#define akey_star_nump kc((row_base+1),(col_base+20))
#define akey_minus_nump kc((row_base+1),(col_base+21))
#define akey7_nump kc((row_base+2),(col_base+16))
#define akey8_nump kc((row_base+2),(col_base+17))
#define akey9_nump kc((row_base+2),(col_base+18))
#define akey_plus_nump kc((row_base+2),(col_base+19))
#define akey4_nump kc((row_base+3),(col_base+16))
#define akey5_nump kc((row_base+3),(col_base+17))
#define akey6_nump kc((row_base+3),(col_base+18))
#define akey1_nump kc((row_base+4),(col_base+13))
#define akey2_nump kc((row_base+4),(col_base+14))
#define akey3_nump kc((row_base+4),(col_base+15))
#define Enter_nump kc((row_base+4),(col_base+16))
#define akey0_nump kc((row_base+5),(col_base+11))
#define akey_dot_nump kc((row_base+5),(col_base+12))
#endif

#ifdef _multimedia
#define mm_www_search kc((row_base+6),(col_base+0))
#define mm_prev_track kc((row_base+6),(col_base+1))
#define mm_www_favorites kc((row_base+6),(col_base+2))
#define mm_www_refresh kc((row_base+6),(col_base+3))
#define mm_volume_down kc((row_base+6),(col_base+4))
#define mm_volume_mute kc((row_base+6),(col_base+5))
#define mm_www_stop kc((row_base+6),(col_base+6))
#define mm_calculator kc((row_base+6),(col_base+7))
#define mm_play_pause kc((row_base+6),(col_base+8))
#define mm_www_back kc((row_base+6),(col_base+9))
#define mm_www_home kc((row_base+6),(col_base+10))
#define mm_stop kc((row_base+6),(col_base+11))
#define mm_mycomp kc((row_base+6),(col_base+12))
#define mm_www_email kc((row_base+6),(col_base+13))
#define mm_next_track kc((row_base+6),(col_base+14))
#define mm_media_select kc((row_base+6),(col_base+15))
#define mm_www_forward kc((row_base+6),(col_base+16))
#define mm_volume_up kc((row_base+6),(col_base+4))
#endif
char lyt_p[]=
{
	F9,0,F5,F3,F1,F2,F12,0,F10,F8,
	F6,F4,Tab,akey_backtick,0,0,RAlt,LShift,0,0,
	LCtrl,akeyq,akey1,0,0,0,akeyz,akeys,akeya,akeyw,
	akey2,0,0,akeyc,akeyx,akeyd,akeye,akey4,akey3,0,
	0,akey_space,akeyv,akeyf,akeyt,akeyr,akey5,0,0,akeyn,
	akeyb,akeyh,akeyg,akeyy,akey6,0,0,0,akeym,akeyj,
	akeyu,akey7,akey8,0,0,akey_comma,akeyk,akeyi,akeyo,akey0,
	akey9,0,0,akey_dot,akey_slash,akeyl,akey_semicolon,akeyp,akey_minus,0,
	0,0,akey_quotes,0,akey_sqrbro,akey_equals,0,0,CapsLock,RShift,
	Enter,akey_sqrbrc,0,akey_bkslash,0,0,0,0,0,0,
	0,0,akey1_nump,0,akey4_nump,akey7_nump,0,0,0,akey0_nump,
	akey_dot_nump,akey2_nump,akey5_nump,akey6_nump,akey8_nump,Esc,NumLock,F11,akey_plus_nump,akey3_nump,
	akey_minus_nump,akey_star_nump,akey9_nump,ScrlLock,0,0,0,0,F7
};

char lyt_s[]=
{
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,mm_www_search,RAlt,0,0,RCtrl,
	mm_prev_track,0,0,mm_www_favorites,0,0,0,0,0,0,
	LGui,mm_www_refresh,mm_volume_down,0,mm_volume_mute,0,0,0,RGui,mm_www_stop,
	0,0,mm_calculator,0,0,0,Option,mm_www_forward,0,mm_volume_up,
	0,mm_play_pause,0,0,ACPI_Power,mm_www_back,0,mm_www_home,mm_stop,0,
	0,0,ACPI_Sleep,mm_mycomp,0,0,0,0,0,0,
	0,mm_www_email,0,akey_slash_nump,0,0,mm_next_track,0,0,mm_media_select,
	0,0,0,0,0,0,0,0,0,Enter_nump,
	0,0,0,ACPI_WakeUp,0,0,0,0,0,0,
	0,0,0,0,End,0,ArrLeft,Home,0,0,
	0,Insert,Delete,ArrDown,0,ArrRight,ArrUp,0,0,0,
	0,PageDown,0,0,PageUp
};
