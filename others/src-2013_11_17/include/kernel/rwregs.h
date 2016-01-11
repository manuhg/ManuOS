#ifndef rwregs_h
#define rwregs_h
 #include <types.h>
 #include <access.h>
 Public uint32 read_cr0();
 Public uint32 read_cr3();
 Public uint32 read_cr4();
 Public uint32 read_eax();
 Public uint32 read_ebx();
 Public uint32 read_ecx();
 Public uint32 read_edx();
 Public uint32 write_cr0(uint32);
 Public uint32 write_cr3(uint32);
 Public uint32 write_cr4(uint32);
 Public uint32 write_eax(uint32);
 Public uint32 write_ebx(uint32);
 Public uint32 write_ecx(uint32);
 Public uint32 write_edx(uint32);
 #endif
