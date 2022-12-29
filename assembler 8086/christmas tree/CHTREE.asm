ROWS	EQU	24d
LINEB	EQU	160d ; bytes per line

_code segment
assume  cs:_code, ss:_stack

start:	mov	ax,_stack
	mov	ss,ax
	mov	sp,offset top	

	mov	ax,0B800h
	mov	es,ax

	call cls

	mov	dl,'A'
	mov	dh,10100000b ; 1 - blinking, 010 - green, 0000 - black
	mov	cx,ROWS
	mov	bl,1 ; count of letters
	mov	bh,lineb
	mov	di,(2 * ROWS - 2)

tree:	mov	bp,cx
	mov	cl,bl
	
	mov	si,di

lett:	cmp	dh,10110000b ; check if carry on 4th bit
	jne	color
	mov	dh,10100000b
color:	cmp	dh,10100010b ; check if green color
	jne	nogre
	inc	dh
nogre:	mov	word ptr es:[di],dx
	inc	dh
	add	di,2
	loop 	lett

	mov	cx,bp

	inc	dl
	add	bl,2

	mov	di,si
	add	di,LINEB
	dec	di
	dec	di

	loop	tree

	mov	ax,0040h;
	mov 	es,ax

	mov	di,0050h;
	mov 	word ptr es:[di],1700h ; set cursor position to 24 row, 1 col

	mov	ah,4ch
	mov	al,0
	int	21h

cls	proc
	xor	ax,ax
	mov	ah,00000111b
	xor	di,di
	mov	cx,2000d ; 80x25
	rep 	stosw
	ret
cls	endp
		
_code ends

_stack segment stack
	dw	100h dup(0)
	top	Label word
_stack ends

end start