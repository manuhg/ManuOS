
global loader				; making entry point visible to linker
global magic
global mbd

extern kernel_main

 

 begin:
 mov byte [0xb8000],'M'
 mov byte [0xb8000],0x20
 ;jmp begin
; reserve initial kernel stack space
STACKSIZE equ 0x4000 ; 16kb.

loader:
     mov  esp, stack + STACKSIZE	 ; set up the stack
     mov  [magic], eax			 ; Multiboot magic number
     mov  [mbd], ebx

     call kernel_main			       ; call kernel proper
     cli
     jmp .hang

.hang:
    hlt 				; halt machine should kernel return
    jmp  .hang



align 4
    dd 0
    dd 0
    dd 0
section .bss
align 4
stack: resb STACKSIZE			; reserve 16k stack on a doubleword boundary
magic: resd 1
mbd:   resd 1
