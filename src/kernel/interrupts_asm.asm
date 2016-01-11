; idt_gdt_isr.asm - primary interrupt handler routines of manuos
; external references to the C kernel:
; idt_ptr
; gdt_ptr
; some user defined irqs (v86) are defined in respective assembly files
[bits 32]
[section .text]
;======externally referred functions/ global functions=========================
global idt_set_1
global idt_set_ptr


global gdt_set_1
global gdt_set_ptr
global isr_h
global irq_h
global int_sti
global int_cli
;==============================================================================

;======external references=====================================================
extern interrupt_handler
extern isr_handler


extern gdt_ptr
extern idt_ptr
;==============================================================================
;==============================================================================
int_sti:
 sti
 ret
int_cli:
 cli
 ret
idt_set_1:
     lidt [idt_ptr]

idt_set_ptr:
     mov eax,[esp+4]
     lidt [eax]
     ret
gdt_set_1:
    lgdt [gdt_ptr]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush2_
.flush2_:
    ret

gdt_set_ptr:
     mov eax,[esp+4]
     lgdt [eax]
     mov ax, 0x10
     mov ds, ax
     mov es, ax
     mov fs, ax
     mov gs, ax
     mov ss, ax
     jmp 0x08:.flush
.flush:
     ret

;==============================================================================
;==============================================================================

isr_h:
   pusha		    ; push edi,esi,ebp,esp,ebx,edx,ecx,eax

   push ds
   push es
   push fs
   push gs


   mov ax, 0x10  ;kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov eax, esp
   push eax

   call isr_handler

   pop eax
   pop gs
   pop fs
   pop es
   pop ds
   popa
   add esp, 8
   iret

irq_h:
   pusha		    ; push edi,esi,ebp,esp,ebx,edx,ecx,eax

   push ds
   push es
   push fs
   push gs


   mov ax, 0x10  ;kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov eax, esp
   push eax

   call interrupt_handler

   pop eax
   pop gs
   pop fs
   pop es
   pop ds

   popa
   add esp, 8
   iret
;==============================================================================
;==============================================================================
global irq_0
global irq_1
global irq_2
global irq_3
global irq_4
global irq_5
global irq_6
global irq_7
global irq_8
global irq_9
global irq_10
global irq_11
global irq_12
global irq_13
global irq_14
global irq_15

global irq_48
global irq_49
global irq_50  
global irq_51
global irq_52
global irq_53
global irq_54
global irq_55
global irq_56
global irq_57
global irq_58
global irq_59
global irq_60  
global irq_61
global irq_62
global irq_63
global irq_64
global irq_65
global irq_66
global irq_67
global irq_68
global irq_69
global irq_70
global irq_71
global irq_72
global irq_73
global irq_74
global irq_75
global irq_76
global irq_77
global irq_78
global irq_79
global irq_80
global irq_81
global irq_82
global irq_83
global irq_84
global irq_85
global irq_86
global irq_87
global irq_88
global irq_89
global irq_90
global irq_91
global irq_92
global irq_93
global irq_94
global irq_95
global irq_96
global irq_97
global irq_98
global irq_99
global irq_100
global irq_100above
;==============================================================================
;==IRQ routines================================================================
;==============================================================================
irq_0:
  cli
  push byte 0 ;error
  push byte 0 ;interrupt number
  jmp irq_h

irq_1:
  cli
  push byte 0 ;error
  push byte 1 ;interrupt number
  jmp irq_h

irq_2:
  cli
  push byte 0 ;error
  push byte 2 ;interrupt number
  jmp irq_h

irq_3:
  cli
  push byte 0 ;error
  push byte 3 ;interrupt number
  jmp irq_h

irq_4:
  cli
  push byte 0 ;error
  push byte 4 ;interrupt number
  jmp irq_h

irq_5:
  cli
  push byte 0 ;error
  push byte 5 ;interrupt number
  jmp irq_h

irq_6:
  cli
  push byte 0 ;error
  push byte 6 ;interrupt number
  jmp irq_h

irq_7:
  cli
  push byte 0 ;error
  push byte 7 ;interrupt number
  jmp irq_h

irq_8:
  cli
  push byte 0 ;error
  push byte 8 ;interrupt number
  jmp irq_h

irq_9:
  cli
  push byte 0 ;error
  push byte 9 ;interrupt number
  jmp irq_h

irq_10:
  cli
  push byte 0  ;error
  push byte 10 ;interrupt number
  jmp irq_h

irq_11:
  cli
  push byte 0  ;error
  push byte 11 ;interrupt number
  jmp irq_h

irq_12:
  cli
  push byte 0  ;error
  push byte 12 ;interrupt number
  jmp irq_h

irq_13:
  cli
  push byte 0  ;error
  push byte 13 ;interrupt number
  jmp irq_h

irq_14:
  cli
  push byte 0  ;error
  push byte 14 ;interrupt number
  jmp irq_h

irq_15: 		;47th interrupt
  cli
  push byte 0  ;error
  push byte 15 ;interrupt number
  jmp irq_h

irq_48: 		
  cli
  push byte 0  ;error
  push byte 48 ;interrupt number
  jmp irq_h

irq_49: 		
  cli
  push byte 0  ;error
  push byte 49 ;interrupt number
  jmp irq_h

irq_50: 		
  cli
  push byte 0  ;error
  push byte 50 ;interrupt number
  jmp irq_h

irq_51: 		
  cli
  push byte 0  ;error
  push byte 51 ;interrupt number
  jmp irq_h

irq_52: 		
  cli
  push byte 0  ;error
  push byte 52 ;interrupt number
  jmp irq_h

irq_53: 		
  cli
  push byte 0  ;error
  push byte 53 ;interrupt number
  jmp irq_h

irq_54: 		
  cli
  push byte 0  ;error
  push byte 54 ;interrupt number
  jmp irq_h

irq_55: 		
  cli
  push byte 0  ;error
  push byte 55 ;interrupt number
  jmp irq_h

irq_56: 		
  cli
  push byte 0  ;error
  push byte 56 ;interrupt number
  jmp irq_h

irq_57: 		
  cli
  push byte 0  ;error
  push byte 57 ;interrupt number
  jmp irq_h

irq_58: 		
  cli
  push byte 0  ;error
  push byte 58 ;interrupt number
  jmp irq_h

irq_59: 		
  cli
  push byte 0  ;error
  push byte 59 ;interrupt number
  jmp irq_h

irq_60: 		
  cli
  push byte 0  ;error
  push byte 60 ;interrupt number
  jmp irq_h

irq_61: 		
  cli
  push byte 0  ;error
  push byte 61 ;interrupt number
  jmp irq_h

irq_62: 		
  cli
  push byte 0  ;error
  push byte 62 ;interrupt number
  jmp irq_h

irq_63: 		
  cli
  push byte 0  ;error
  push byte 63 ;interrupt number
  jmp irq_h

irq_64: 		
  cli
  push byte 0  ;error
  push byte 64 ;interrupt number
  jmp irq_h

irq_65: 		
  cli
  push byte 0  ;error
  push byte 65 ;interrupt number
  jmp irq_h

irq_66: 		
  cli
  push byte 0  ;error
  push byte 66 ;interrupt number
  jmp irq_h

irq_67: 		
  cli
  push byte 0  ;error
  push byte 67 ;interrupt number
  jmp irq_h

irq_68: 		
  cli
  push byte 0  ;error
  push byte 68 ;interrupt number
  jmp irq_h

irq_69: 		
  cli
  push byte 0  ;error
  push byte 69 ;interrupt number
  jmp irq_h

irq_70: 		
  cli
  push byte 0  ;error
  push byte 70 ;interrupt number
  jmp irq_h

irq_71: 		
  cli
  push byte 0  ;error
  push byte 71 ;interrupt number
  jmp irq_h

irq_72: 		
  cli
  push byte 0  ;error
  push byte 72 ;interrupt number
  jmp irq_h

irq_73: 		
  cli
  push byte 0  ;error
  push byte 73 ;interrupt number
  jmp irq_h

irq_74: 		
  cli
  push byte 0  ;error
  push byte 74 ;interrupt number
  jmp irq_h

irq_75: 		
  cli
  push byte 0  ;error
  push byte 75 ;interrupt number
  jmp irq_h

irq_76: 		
  cli
  push byte 0  ;error
  push byte 76 ;interrupt number
  jmp irq_h

irq_77:
  cli
  push byte 0  ;error
  push byte 77 ;interrupt number
  jmp irq_h

irq_78: 		
  cli
  push byte 0  ;error
  push byte 78 ;interrupt number
  jmp irq_h

irq_79: 		
  cli
  push byte 0  ;error
  push byte 79 ;interrupt number
  jmp irq_h

irq_80: 		
  cli
  push byte 0  ;error
  push byte 80 ;interrupt number
  jmp irq_h

irq_81: 		
  cli
  push byte 0  ;error
  push byte 81 ;interrupt number
  jmp irq_h

irq_82: 		
  cli
  push byte 0  ;error
  push byte 82 ;interrupt number
  jmp irq_h

irq_83: 		
  cli
  push byte 0  ;error
  push byte 83 ;interrupt number
  jmp irq_h

irq_84: 		
  cli
  push byte 0  ;error
  push byte 84 ;interrupt number
  jmp irq_h

irq_85: 		
  cli
  push byte 0  ;error
  push byte 85 ;interrupt number
  jmp irq_h

irq_86: 		
  cli
  push byte 0  ;error
  push byte 86 ;interrupt number
  jmp irq_h

irq_87: 		
  cli
  push byte 0  ;error
  push byte 87 ;interrupt number
  jmp irq_h

irq_88: 		
  cli
  push byte 0  ;error
  push byte 88 ;interrupt number
  jmp irq_h

irq_89: 		
  cli
  push byte 0  ;error
  push byte 89 ;interrupt number
  jmp irq_h

irq_90: 		
  cli
  push byte 0  ;error
  push byte 90 ;interrupt number
  jmp irq_h

irq_91: 		
  cli
  push byte 0  ;error
  push byte 91 ;interrupt number
  jmp irq_h

irq_92: 		
  cli
  push byte 0  ;error
  push byte 92 ;interrupt number
  jmp irq_h

irq_93: 		
  cli
  push byte 0  ;error
  push byte 93 ;interrupt number
  jmp irq_h

irq_94: 		
  cli
  push byte 0  ;error
  push byte 94 ;interrupt number
  jmp irq_h

irq_95: 		
  cli
  push byte 0  ;error
  push byte 95 ;interrupt number
  jmp irq_h

irq_96: 		
  cli
  push byte 0  ;error
  push byte 96 ;interrupt number
  jmp irq_h

irq_97: 		
  cli
  push byte 0  ;error
  push byte 97 ;interrupt number
  jmp irq_h

irq_98: 		
  cli
  push byte 0  ;error
  push byte 98 ;interrupt number
  jmp irq_h

irq_99: 		
  cli
  push byte 0  ;error
  push byte 99 ;interrupt number
  jmp irq_h

irq_100:		
  cli
  push byte 0  ;error
  push byte 100 ;interrupt number
  jmp irq_h

irq_100above:
  cli
  push byte 0  ;error
  push byte 101 ;interrupt number
  jmp irq_h
  
;==============================================================================
;==============================================================================


;======ISRS====================================================================

;======externally referred functions/ global functions=========================
global isr_0
global isr_1
global isr_2
global isr_3
global isr_4
global isr_5
global isr_6
global isr_7
global isr_8
global isr_9
global isr_10
global isr_11
global isr_12
global isr_13
global isr_14
global isr_15
global isr_16
global isr_17
global isr_18
global isr_19
global isr_20
global isr_21
global isr_22
global isr_23
global isr_24
global isr_25
global isr_26
global isr_27
global isr_28
global isr_29
global isr_30
global isr_31
;==============================================================================
;======fault and exception handlers============================================
;  0: Divide By Zero Exception
isr_0:
    cli
    push byte 0
    push byte 0
    jmp isr_h

;  1: Debug Exception
isr_1:
    cli
    push byte 0
    push byte 1
    jmp isr_h

;  2: Non Maskable Interrupt Exception
isr_2:
    cli
    push byte 0
    push byte 2
    jmp isr_h

;  3: Int 3 Exception
isr_3:
    cli
    push byte 0
    push byte 3
    jmp isr_h

;  4: INTO Exception
isr_4:
    cli
    push byte 0
    push byte 4
    jmp isr_h

;  5: Out of Bounds Exception
isr_5:
    cli
    push byte 0
    push byte 5
    jmp isr_h

;  6: Invalid Opcode Exception
isr_6:
    cli
    push byte 0
    push byte 6
    jmp isr_h

;  7: Coprocessor Not Available Exception
isr_7:
    cli
    push byte 0
    push byte 7
    jmp isr_h

;  8: Double Fault Exception (With Error Code!)
isr_8:
    cli
    push byte 8
    jmp isr_h

;  9: Coprocessor Segment Overrun Exception
isr_9:
    cli
    push byte 0
    push byte 9
    jmp isr_h

; 10: Bad TSS Exception (With Error Code!)
isr_10:
    cli
    push byte 10
    jmp isr_h

; 11: Segment Not Present Exception (With Error Code!)
isr_11:
    cli
    push byte 11
    jmp isr_h

; 12: Stack Fault Exception (With Error Code!)
isr_12:
    cli
    push byte 12
    jmp isr_h

; 13: General Protection Fault Exception (With Error Code!)
isr_13:
    cli
    push byte 13
    jmp isr_h

; 14: Page Fault Exception (With Error Code!)
isr_14:
    cli
    push byte 14
    jmp isr_h

; 15: Reserved Exception
isr_15:
    cli
    push byte 0
    push byte 15
    jmp isr_h

; 16: Floating Point Exception
isr_16:
    cli
    push byte 0
    push byte 16
    jmp isr_h

; 17: Alignment Check Exception
isr_17:
    cli
    push byte 0
    push byte 17
    jmp isr_h

; 18: Machine Check Exception
isr_18:
    cli
    push byte 0
    push byte 18
    jmp isr_h

; 19: Reserved
isr_19:
    cli
    push byte 0
    push byte 19
    jmp isr_h

; 20: Reserved
isr_20:
    cli
    push byte 0
    push byte 20
    jmp isr_h

; 21: Reserved
isr_21:
    cli
    push byte 0
    push byte 21
    jmp isr_h

; 22: Reserved
isr_22:
    cli
    push byte 0
    push byte 22
    jmp isr_h

; 23: Reserved
isr_23:
    cli
    push byte 0
    push byte 23
    jmp isr_h

; 24: Reserved
isr_24:
    cli
    push byte 0
    push byte 24
    jmp isr_h

; 25: Reserved
isr_25:
    cli
    push byte 0
    push byte 25
    jmp isr_h

; 26: Reserved
isr_26:
    cli
    push byte 0
    push byte 26
    jmp isr_h

; 27: Reserved
isr_27:
    cli
    push byte 0
    push byte 27
    jmp isr_h

; 28: Reserved
isr_28:
    cli
    push byte 0
    push byte 28
    jmp isr_h

; 29: Reserved
isr_29:
    cli
    push byte 0
    push byte 29
    jmp isr_h

; 30: Reserved
isr_30:
    cli
    push byte 0
    push byte 30
    jmp isr_h

; 31: Reserved
isr_31:
    cli
    push byte 0
    push byte 31
    jmp isr_h

;==============================================================================
;==============================================================================
