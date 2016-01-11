	BITS 16

start:

;
;       Writing to the hard disk using the ports!     by qark
;       +---------------------------------------+
;
;  The only differences between reading and writing using the ports is
;  that 30h is sent to the command register, and instead of INSW you
;  OUTSW. 
;

   mov	   dx,1f6h	   ;Drive and head port
   mov	   al,0a0h	   ;Drive 0, head 0
   out	   dx,al

   mov	   dx,1f2h	   ;Sector count port
   mov	   al,1 	   ;Write one sector
   out	   dx,al

   mov	   dx,1f3h	   ;Sector number port
   mov	   al,1 	  ;Wrote to sector one
   out	   dx,al

   mov	   dx,1f4h	   ;Cylinder low port
   mov	   al,0 	   ;Cylinder 0
   out	   dx,al

   mov	   dx,1f5h	   ;Cylinder high port
   mov	   al,0 	   ;The rest of the cylinder 0
   out	   dx,al

   mov	   dx,1f7h	   ;Command port
   mov	   al,30h	   ;Write with retry.
   out	   dx,al

oogle:
   in	   al,dx
   test    al,8 	   ;Wait for sector buffer ready.
   jz	   oogle

   mov	   cx,512	 ;One sector
   mov	   si,0
   mov	   dx,1f0h	   ;Data port - data comes in and out of here.
   rep	   outsw	   ;Send it.
blah:
   mov ah,0
   mov ax,4f02h
   mov bx,113h
   int 10h
xxx: jmp xxx

;buffer:  times 20 db 0
	times 510-($-$$) db 0	; Pad remainder of boot sector with 0s
	dw 0xAA55		; The standard PC boot signature