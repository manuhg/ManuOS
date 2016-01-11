#ifndef printf_h
#define printf_h
#include <access.h> 
 Public size_t strnlen(const char *s, size_t maxlen);
 Public int vsprintf(char *buf, const char *fmt, va_list args);
 Public int sprintf(char *buf, const char *fmt, ...);
 Public int printf(const char *fmt, ...); 
 
 #define _other_args_for_mprintf
int mprintf(int colour,const char *fmt 
  #ifdef _other_args_for_mprintf
 , ... 
 #endif
 );
 #endif
