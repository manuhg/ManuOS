	BITS 16

start:
	mov ax, 07C0h		; Set up 4K stack space after this bootloader
	add ax, 288		; (4096 + 512) / 16 bytes per paragraph
	mov ss, ax
	mov sp, 4096

	mov ax, 07C0h		; Set data segment to where we're loaded
	mov ds, ax
xyz:	mov dl,0h
	call write
	mov dl,1h
	call write
	mov dl,80h
	call write
	mov dl,81h
	call write
	jmp yyy

write:	mov ax,0
	mov es,ax
	mov al,2
	mov ch,0
	mov cl,1
	mov dh,0
	mov bx,buffer
	ret
yyy:	cmp cf,1
blah:
	;je blah
	mov ah,0
	mov ax,4f02h
	mov bx,113h
	int 10h
	mov ah,0ch
	mov bh,0
	mov al,4
	mov cx,0
	mov dx,0
done:
	jmp done

buffer: times 20 db 0
	times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
	dw 0xAA55		; The standard PC boot signature