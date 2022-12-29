_code segment
assume  cs:_code, ss:_stack

start:	mov	ax,_stack
	mov	ss,ax
	mov	sp,offset top

	mov	ah,00h ; set video mode 80x25
	mov	al,03h
	int	10h

rows	EQU	24d
col	EQU	23d ; position of center column

	mov	al,'A'
	mov	bh,00h ; number of video page
	mov	bl,11111011b ; 1 - blink, 111 - light gray, 1011 - light cyan
	mov	cx,01h ; number of characters to display
	mov	si,rows
petla:	mov	ah,02h
	mov	dl,rows ; calculate row position
	sub	dx,si
	mov	dh,dl
	mov	dl,col ; calculate column position
	sub	dl,dh
	int	10h

	mov	ah,09h
	int	10h
	add	cx,02h
	inc	al
	dec	si
	jnz	petla

	mov	ah,4ch
	mov	al,0
	int	21h
_code ends

_stack segment stack
	dw	100h dup(0)
top	Label word
_stack ends

end start