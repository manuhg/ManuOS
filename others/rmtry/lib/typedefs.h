#ifndef typedefs_h
#define typedefs_h
#include "types.h"
#ifndef _nstvartypes //typedefs from structs

struct gdt_entry_bits
{
	uint32 limit_low:16;
	uint32 base_low : 24;
     //attribute byte split into bitfields
	uint32 accessed :1;
	uint32 read_write :1; //readable for code, writable for data
	uint32 conforming_expand_down :1; //conforming for code, expand down for data
	uint32 code :1; //1 for code, 0 for data
	uint32 always_1 :1; //should be 1 for everything but TSS and LDT
	uint32 DPL :2; //priveledge level
	uint32 present :1;
     //and now into granularity
	uint32 limit_high :4;
	uint32 available :1;
	uint32 always_0 :1; //should always be 0
	uint32 big :1; //32bit opcodes for code, dword stack for data
	uint32 gran :1; //1 to use 4k page addressing, 0 for byte addressing
	uint32 base_high :8;
} __packed; //or __attribute__((packed))

struct idt_entry_s{
   uint16 base_low;    // The lower 16 bits of the address to jump to when this interrupt occures: offset 0-15
   uint16 selector;      // Kernel segment selector in IDT
   uint8  zero;          // This must always be zero.
   uint8  flags;    //gate types, atttribute types etc.
   uint16 base_high;   // The upper 16 bits of the address to jump to. offset 16-31
} __attribute__((packed));

typedef struct idt_entry_s idt_entry_t;

struct idt_ptr_s_ {
    uint16 limit;
    uint32 base;     
} __attribute__((packed));
typedef struct idt_ptr_s_ idt_ptr_t;

struct gdt_entry_s
{
   uint16 limit_low;           // The lower 16 bits of the limit.
   uint16 base_low;            // The lower 16 bits of the base.
   uint8  base_middle;         // The next 8 bits of the base.
   uint8  access;              // Access flags, determine what ring this segment can be used in.
   uint8  granularity;         // eg: 4kb means 32 bit opcodes
   uint8  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_s gdt_entry_t;

struct gdt_ptr_s_
{
   uint16 limit;               // The upper 16 bits of all selector limits.
   uint32 base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_s_ gdt_ptr_t; 

typedef struct registers_s
{
    uint32 gs, fs, es, ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;
} regs_t;

typedef struct 
{
	int32 date;
	int8 name[3];
}
day;

typedef unsigned long int binary;// defining binary data type
typedef long  sbinary; 
#endif

#endif
