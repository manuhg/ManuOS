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

#endif
