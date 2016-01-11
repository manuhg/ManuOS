#ifndef cpu_h
#define cpu_h
#include <access.h>
typedef struct cpu_features_s
{
	char vendor_str[13];
	uint32 ebx,edx,ecx;
}__attribute__((packed)) cpu_features_t;
enum cpu_cpuidvals {
  cpuid_vendor_str,
  cpuid_features,
  cpuid_tlb,
  cpuid_serial,
 
  cpuid_intel_extended=0x80000000,
  cpuid_intel_features,
  cpuid_intel_brand_str,
  cpuid_intel_brand_str_more,
  cpuid_intel_brand_str_end,
};
 Public cpu_features_t cpu_features;
 Public void cpu_init();

#endif
