;Acessing pci bus
[bits 32]

global read_data_port
extern printf

;Bus             EQU     [esp+16]
;Device          EQU     [esp+12]
;Function        EQU     [esp+8]
;Vendor_ID       EQU     [esp+4]		; vendor ID=PCI regs 0,1
PCI_INDEX       EQU     0CF8h
PCI_DATA        EQU     0CFCh

;Bus db 0
;Device db 0
;Function db 0
;Vendor_ID db 0

section .text

read_data_port:
;mov eax,[esp+16]
;mov [Bus],eax
;mov eax,[esp+12]
;mov [Device],eax
;mov eax,[esp+8]
;mov [Function],eax
;mov eax,[esp+4]
;mov [Vendor_ID],eax

mov ax, 8000h               ; set bit 31 (after shift)
or  al, [esp+16]                 ; add in bus number
shl eax, 16                 

mov ax,[esp+12]
shl ax,11                  ; slide device # up to bits 15:11
mov al,[esp+8]
or  ah,al                  ; add function into bits 10:8
mov al,[esp+4]

cli
mov dx,PCI_INDEX
out dx,eax                 ; send our request out

mov dx,PCI_DATA            
in  eax,dx                 ; read back 32bit value.
sti

ret


;section .bss
 
;align 4
;
;Bus: resd 1
;Device: resd 1
;Function: resd 1
;Vendor_ID: resd 1


