BUFFER_SIZE	EQU	1024

_code segment

assume cs:_code, ss:_stack, ds:_data, es:_esegment

start:
	mov	ax,_stack
	mov	ss,ax
	mov	sp,offset top

	mov	ax,_data ; loading program argument
	mov	es,ax
	mov	di,offset argument
	xor	cx,cx
	mov	cl,ds:[80h]
	cmp	cl,0
	jne	loadarg
	mov	ds,ax
	jmp	printhelp
loadarg:
	sub	cl,1
	mov	si,82h
	rep	movsb
	mov	byte ptr [di+1],0

	mov	ds,ax ; loading segment registers 
	mov	ax,_esegment
	mov	es,ax

	mov	al,0 ; opening existing file to read
	mov	dx,offset argument
	mov	ah,3dh
	int	21h
	jnc	fileread
	jmp	fileerr

fileread:
	mov	bx,ax ; reading notes from file - passing file handle
	mov	dx,offset buffer
	mov	cx,BUFFER_SIZE
	mov	ah,3fh
	int	21h
	jnc	fileclose
	jmp	fileerr

fileclose:
	mov	ah,3eh ; closing file
	int	21h
	jnc	videoconf
	jmp	fileerr

videoconf:
	mov	ah,00h ; setting video mode 80x25
	mov	al,03h
	int	10h

	mov	dl,0
	mov	dh,1
	mov	ah,02h ; setting cursor
	mov	bh,00h
	int	10h

	mov	ah,09h ; display author tag
	mov	dx,offset author
	int	21h

	;mov al,10110110b ; configuring 8253 | 10 - 2nd timer, 11 - little endian, 011 - square wave generator, 0 - 16 bit mode
	;out 43h,al ; send control word to control word register

	mov	si,offset buffer
	mov	bp,2

mainloop:
	mov	dx,bp
	lodsw ; loading note frequency ax <- ds:si
	mov	di,ax
	cmp	ax,0
	jne	display
	jmp	end

display: ; ax = di
	cmp	dl,79
	jl	level1

	mov	ah,07h ; clearing screen
	mov	al,00h
	mov	ch,2 ; top-left corner
	mov	cl,0
	mov	dh,24 ; bottom-right corner
	mov	dl,79
	xor	bh,bh
	int	10h

	mov	dl,2

level1: ; sampling
	cmp	di,2415 ; (1193000/494)
	jg	level2
	mov	dh,2
	jmp	setattr
level2:
	cmp	di,2711 ; (1193000/440)
	jg	level3
	mov	dh,5
	jmp	setattr
level3:
	cmp	di,3043 ; (1193000/392)
	jg	level4
	mov	dh,8
	jmp	setattr
level4:
	cmp	di,3324 ; (1193000/370)
	jg	level5
	mov	dh,11
	jmp	setattr
level5:
	cmp	di,3615 ; (1193000/330)
	jg	level6
	mov	dh,14
	jmp	setattr
level6:
	cmp	di,4058 ; (1193000/294)
	jg	level7
	mov	dh,17
	jmp	setattr
level7:
	cmp	di,9107 ; (1193000/131)
	jg	level8
	mov	dh,20
	jmp	setattr
level8:
	mov	dh,23
setattr:
	mov	bx,1
	mov	al,'#'
	mov	cx,5
printcol:
	cmp	dh,25
	je	proceed

	mov	ah,02h ; setting cursor
	int	10h

	mov	ah,09h ; writing character on cursor position
	int	10h

	inc	dh
	cmp	bl,00001111b
	jne	skip
	mov	bl,0
skip:
	inc	bl
	jmp	printcol

proceed:
	add	dl,7

	mov	bp,dx
	mov	ax,di

	out	42h,al ; sending frequency to 8253 PIT
	mov	al,ah
	out	42h,al
	in	al,61h ; turning on speaker data and speaker - timer 2 gate - 8255 PPI
	or	al,00000011b
	out	61h,al

	lodsw ; loading duration of note playing
	mov	dx,ax
	lodsw
	mov	cx,ax
	mov	bx,si ;---
	xor	si,si ;---
	mov	ah,86h ; BIOS wait function
	int	15h
	mov	si,bx ;---

	in	al,61h ; turning off speaker data and speaker - timer 2 gate
	and	al,11111100b
	out	61h,al

	lodsw ; loading pause between notes
	mov	dx,ax
	lodsw
	mov	cx,ax
	mov	bx,si ;---
	xor	si,si ;---
	mov	ah,86h
	int	15h
	mov	si,bx ;---

	jmp	mainloop

fileerr:
	mov	ah,09h
	mov	dx,offset ferror
	int	21h
	jmp	end

printhelp:
	mov	ah,09h
	mov	dx,offset help
	int	21h
end:
	mov	ah,4ch
	mov	al,00h
	int	21h
_code ends

_data segment
author	db	"Program Melodia - Autorzy: Dominik Jalowiecki",'$'
help		db	"Blad! Podaj plik z melodia jako argument programu np. 'MELODY.exe NOTES1.bin'",'$'
ferror	db	"Blad! Nie udalo sie otworzyc podanego pliku...",'$'
argument	db	126	dup(?)
buffer	dw	BUFFER_SIZE	dup(0)
_data ends

_esegment segment
	dw	24	dup(0) ;--- DOSBox v0.74-3 int 15h ah 86h bug workaround
_esegment ends

_stack segment stack
	dw	100h	dup(0)
top	Label	word
_stack ends

end start