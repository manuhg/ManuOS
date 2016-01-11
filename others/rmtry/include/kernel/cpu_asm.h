#ifndef cpu_asm_h
#define cpu_asm_h
 #include <types.h>
 #include <access.h>
 Public int cpu_cpuid_supported();
 Public char *cpu_find_vendorID();
 Public uint32 dword_byterev(uint32);
 Public uint32 *cpu_find_features();
 Public uint32 _ebx_val;
 Public uint32 _edx_val;
 Public uint32 _ecx_val;
 #endif
