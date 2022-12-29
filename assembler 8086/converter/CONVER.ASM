_code segment
assume  cs:_code, ds:_data, ss:_stack

start:	mov	ax,_data
	mov	ds,ax
	mov	ax,_stack
	mov	ss,ax
	mov	sp,offset top

	mov	ah,09h
	mov	dx,offset welcometxt
	int	21h

	jmp	inp

err:	mov	ah,09h
	mov	dx,offset errortxt
	int	21h

inp:	mov	bh,0
	mov	dx,offset inputtxt
	int	21h

	mov	cl,3 ; digit counter
	mov	dh,00110000b ; digit mask
	xor	dl,dl
	mov	ah,01h

getdig:	int	21h
	cmp	cl,3 ; if not first digit
	je	noent
	cmp	al,0Dh ; check if is enter
	je	proce
noent:	xor	al,dh
	cmp	al,0Ah ; check if is valid digit
	jge	err
	cmp	cl,3 ; if is first digit
	jne	nozer
	cmp	al,dl	; check if is 0
	je	nline
nozer:	cmp	cl,2
	jg	stdig
	je	nddig
	mov	ch,al
	jmp	cont
nddig:	mov	bl,al
	jmp	cont
stdig:	mov	bh,al
cont:	dec	cl
	jnz	getdig

valid:	cmp	bh,2 ; validate max 255
	jg	err
	jl	nline
	cmp	bl,5
	jg	err
	jl	nline
	cmp	ch,5
	jg	err

nline:	mov	ah,09h
	mov	dx,offset crlf
	int	21h

proce:	cmp	cl,1
	mov	al,bh
	jg	display ; units
	jl	hundr
	mov	al,10	; tens
	mul	bh
	add	al,bl
	jmp	display
hundr:	mov	al,100 ; hundreds
	mul	bh
	mov	bh, al
	mov	al,10
	mul	bl
	add	al,bh
	add	al,ch

display:	mov	ah,09h ; bin
	mov	dx,offset bintxt
	int	21h

	mov	bh,al
	mov	bl,bh
	mov	ah,02h
	mov	cx,8
bin:	shl 	bh,1
	jnc	dzer
	mov	dl,00110001b
	jmp	prnt
dzer:	mov	dl,00110000b
prnt: int	21h
	loop	bin

	mov	ah,09h ; hex
	mov	dx,offset hextxt
	int	21h
	mov	bh,00110000b

	mov	ah,02h
	mov	dl,bl
	shr	dl,4
	or	dl,bh
	cmp	dl,00111001b
	jng	skip1
	add	dl,7
skip1:	int	21h
	
	mov	dl,bl
	and	dl,00001111b
	or	dl,bh
	cmp	dl,00111001b
	jng	skip2
	add	dl,7
skip2:	int	21h

	mov	ah,4ch
	mov	al,0
	int	21h
_code ends

_data segment
welcometxt	db	"Konwersja liczby dziesietnej od 0 do 255 na zapis binarny i heksadecymalny.",13,10,"Autor: Dominik Jalowiecki",13,10,10,'$'
inputtxt	db	"Wprowadz liczbe: ",'$'
bintxt		db	13,10,"Zapis binarny liczby: ",'$'
hextxt		db	13,10,"Zapis heksadecymalny liczby: ",'$'
errortxt	db	13,10,"BLAD! Wpisana liczba powinna byc z zakresu od 0 do 255...",13,10,10,'$'
crlf		db	13,10,'$'
_data ends

_stack segment stack
	dw	100h dup(0)
top	Label word
_stack ends

end start