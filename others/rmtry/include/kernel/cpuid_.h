#ifndef cpuid__h
#define cpuid_
#include <access.h>

 #define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
 Public void detect_cpu();
 Public void intel();
 Public void amd();
 Public void printregs(int eax, int ebx, int ecx, int edx);
 #define printf _printf
#endif
