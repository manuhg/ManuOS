#ifndef string_h
#define string_h
/*
#ifndef Private
 #define Private
 #endif
#ifndef Public
 #define Public
 #endif

#ifndef internal*/
 #ifdef Public
  #undef Public
 #endif
 #define Public extern
//#endif

#include <typedefs.h>
#include <defines.h>


 Public size_t strlen(char *str);
 Public int strcmp(const char *str1,const char *str2);
 Public void strrev(char *str);
 Public char *strcpy(char *dest,char *src);
 Public int strncmp(const char *cs, const char *ct, size_t count);
 Public size_t strnlen(const char *s, size_t maxlen);
 Public char *strncpy(char *dest,char *src,size_t max_len);

#endif
