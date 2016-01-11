[bits 16]

section .text
pmode_to_rmode:
mov	     eax, cr0
      and	   eax, 7FFFFFFEh   
      mov	   cr0, eax
      ;set up real mode segment registers and stack
      mov	   esp, realmode_stack_top	    ;modify it to your needs!
      xor	   ax, ax
      mov	   ds, ax
      mov	   es, ax
      mov	   fs, ax
      mov	   gs, ax
      mov	   ss, ax

section .data
    align  16
    rm_gdt_ptr:
      dw rm_gdtend-rm_gdt-1
      dd rm_gdt,0
    align  16

   rm_gdt:
      dd 0,0			  ;null descriptor
     DESC_DATA equ 8				     ;descriptor in YOUR GDT (modify)
     DESC_LONG equ $-rm_gdt
      dd 00000000h,00209800h	  ;64 bit long mode cs
     DESC_REAL equ $-rm_gdt
      dd 0000FFFFh,00009801h	  ;16 bit real mode cs (modify base if needed!)
  rm_gdtend:
  align        16
  rm_idt_ptr:
   dw 3ffh
   dd 0