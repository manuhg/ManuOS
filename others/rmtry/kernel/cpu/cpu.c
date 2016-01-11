#include <stdio.h>
#include <kernel/cpu_asm.h>
#include <kernel/rwregs.h>
#include <kernel/cpuid_.h>
#define internal
#include "cpu.h"
cpu_features_t cpu_features;
void cpu_init()
{
	//_printf("\n\t CPU Vendor String : ");strcpy(cpu_features.vendor_str,cpu_find_vendorID());
	//_printf(cpu_features.vendor_str);	
	_printf("\nDetecting the processor:\n");
	detect_cpu();
}
