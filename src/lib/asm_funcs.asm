[BITS 32]

global read_ata_disk
global insl_
insl_:
	push	ebp
	mov	ebp, esp
	cld
	push	edi
	mov	edx, [ebp+8]		 ; port
	mov	edi, [ebp+12]		 ; buf
	mov	ecx, [ebp+16]		 ; byte count
	shr	ecx, 2			 ; dword count
       ; rep  ins                         ;input many dwords
	pop	edi
	pop	ebp
	ret

asm_printbyte:
   mov eax,[esp+4]
   mov ecx,[esp+1]
   mov [0xb8000+eax],ecx
   ret

cpu_speed:
;     cli
;     mov al,0x43 ;PTT's port
;     out al,0x34 ;set timer -one shot mode
;     mov al,0x40
;     out al,0
;     out al,0
;     mov ebx,0
;cycles:
;     add ebx,1
;     cmp ebx,0x10000
;     jne cycles
;     in al,0x40
;     push ax
;     ret

get_rtc:
     push ebp
     cli
     mov al,[esp+1]
     ;mov al,eax
     out 0x70,al
     in al,0x71
     sti
     pop ebp
     ret
extern v86_set_vmbit

global uirq_48

uirq_48: ;for v86mode switch
   push byte 0
   push byte 48

uirq_h_48:
   pusha		    ; push edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds		    ; Lower 16-bits of eax = ds.
   push eax


   mov ax, 0x10  ;kernel data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax

   call v86_set_vmbit

   pop eax	  ;original data segment descriptor
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax

   popa
   add esp, 8
   iret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

