#ifndef printf_h
#define printf_h
#include <access.h> 
#include <stdio.h>
 Public size_t strnlen(const char *s, size_t maxlen);
 Public int vsprintf(char *buf, const char *fmt, va_list args);
 Public int sprintf(char *buf, const char *fmt, ...);
 Public int printf(const char *fmt, ...);
 Public int puts_sl(const char *str,size_t len);
 Public int puts(const char *str);
 Public int kfprintf(const char *fmt, ...);
 Public int kfprintf_print();
 Public int kfprintf_bufclear();
 
 #define _other_args_for_mprintf
int mprintf(int colour,const char *fmt 
  #ifdef _other_args_for_mprintf
 , ... 
 #endif
 );
 #endif
