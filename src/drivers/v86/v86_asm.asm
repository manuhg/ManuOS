[bits 32]
global set_nt_eflsgs
set_nt_eflsgs:
    pushfd
    xor ax,ax
    mov ax,1
    shl ax,14 ;lesft shift
    or [esp],ax
    popfd
    ret

global v86_detect_v86
v86_detect_v86:
   smsw ax
   and	eax,1
   ret


;==============================================================================
;==============================================================================
[bits 16]
global	int86_asm
int86_asm:
;                push    bp
;                mov     bp,sp
;                push    si
;                push    di
;                push    ds
;                push    bp
;                mov     ax,[bp+4]
;                mov     byte ptr cs:[word ptr selfx+1],al
;                mov     bx,[bp+6]
;                mov     cx,[bx+4]
;                mov     dx,[bx+6]
;                mov     si,[bx+8]
;                mov     di,[bx+0Ah]
;                mov     bp,[bx+0Ch]
;                mov     ax,[bx+2]
;                push    ax
;                mov     ax,[bx]
;                push    ax
;                mov     ax,[bx+10h]
;                mov     es,ax
;                push    word ptr [bx+12h]
;                mov     ax,[bx+0Eh]
;                mov     ds,ax
;                popf                            ; Pop flags
;                pop     ax
;                pop     bx
;selfx:          int     19h                     ; Bootstrap loader
;                push    bp
;                mov     bp,sp
;                xchg    bx,[bp+2]
;                mov     bp,bx
;                mov     bx,ds
;                xchg    bx,[bp-6]
;                mov     ds,bx
;                mov     bx,[bp+8]
;                pushf                           ; Push flags
;                pop     word ptr [bx+12h]
;                mov     [bx],ax
;                mov     [bx+4],cx
;                mov     [bx+6],dx
;                mov     [bx+8],si
;                mov     [bx+0Ah],di
;                mov     ax,es
;                mov     [bx+10h],ax
;                pop     word ptr [bx+0Ch]
;                pop     word ptr [bx+2]
;                pop     word ptr [bx+0Eh]
;                pop     di
;                pop     si
;                pop     bp
		ret


global set_vdio_mode
set_vdio_mode:
   mov ah,00h
   mov al,13h
   ret