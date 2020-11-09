; Autor: Kamil Cinner
;

; inicjalizacja wska�nika stosu
ldi	R16, LOW(RAMEND)		; za�adowanie adresu ko�ca pami�ci[sta�a RAMEND - zdefiniowana w pliku m32def.inc z katalogu dependencies projektu](starszej jego cz��i) SRAM do R16
out	SPL, R16				; za�adowanie zawarto�ci rejestru R16 do SPH(starszej cz��i) rejestru kt�ry przechowuje tzw. wska�nik ko�ca stosu
ldi	R16, HIGH(RAMEND)		; za�adowanie (mlodszej czesci) adresu konca pamieci SRAM do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru kt�ry przechowuje wska�nik ko�ca stosu(m�odszej cz�ci)

sbi DDRA, 0					; ustaw pin PA.0 jako linia wyj�ciowa
sbi DDRA, 1					; ustaw pin PA.1 jako linia wyj�ciowa
sbi DDRA, 2					; ustaw pin PA.2 jako linia wyj�ciowa

main:						; program g��wny
    rcall setBits500		; wywo�aj procedur� ustawiaj�c� pierwsze trzy bity rejestru PORTA w ustawieniu dla op�nienia 500ms
	rcall delay250			; wywo�aj procedur� op�nienia
	rcall delay250			; wywo�aj procedur� op�nienia
	rcall setBits250		; wywo�aj procedur� ustawiaj�c� pierwsze trzy bity rejestru PORTA w ustawieniu dla op�nienia 250ms
	rcall delay250			; wywo�aj procedur� op�nienia
	rjmp main				; wr�� na pocz�tek programu g��wnego

setBits500:					; ustaw bity rejestru PORTA dla op�nienia 500ms
	cbi PORTA, 0			; ustaw PA.0=0
	sbi PORTA, 1			; ustaw PA.1=1
	cbi PORTA, 2			; ustaw PA.2=0
	ret						; powr�� z podprogramu

setBits250:					; ustaw bity rejestru PORTA dla op�nienia 250ms
	sbi PORTA, 0			; ustaw PA.0=1

; ustaw PA.1 w zale�no�ci od PA.3
	sbis PINA, 3			; je�li PA.3=1, to pomi� nast�pn� instrukcj�
	sbi PORTA, 1			; ustaw PA.1=1
	sbic PINA, 3			; je�li PA.3=0, to pomi� nast�pn� instrukcj�
	cbi PORTA, 1			; ustaw PA.1=0

	sbi PORTA, 2			; ustaw PA.2=1
	ret						; powr�� z podprogramu

delay250:					; p�tla op�niaj�ca o 250ms (250 000 cykli)
; 249 999 cykli:
			ldi  R17, $A7	; za�adowanie warto�ci $A7 (hex) do rejestru R17
WGLOOP0:	ldi  R18, $02	; za�adowanie warto�ci $02 (hex) do rejestru R18
WGLOOP1:	ldi  R19, $F8	; za�adowanie warto�ci $F8 (hex) do rejestru R19
WGLOOP2:	dec  R19		; zmniejsz warto�� rejestru R19 o 1, je�eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP2	; je�li wynik ostatniej operacji dekrementowania jest r�ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP2
			dec  R18		; zmniejsz warto�� rejestru R18 o 1, je�eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP1	; je�li wynik ostatniej operacji dekrementowania jest r�ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP1
			dec  R17		; zmniejsz warto�� rejestru R17 o 1, je�eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP0	; je�li wynik ostatniej operacji dekrementowania jest r�ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP0
; 1 cykl:
			nop				; nie r�b nic przez 1 cykl
			ret				; wro� z podprogramu
