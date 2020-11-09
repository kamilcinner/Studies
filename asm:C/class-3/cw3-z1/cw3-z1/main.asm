;
; cw3-z1.asm
;
; Created: 10/12/2020 6:30:37 PM
; Author : Kamil Cinner
;

; inicjalizacja wska�nika stosu
ldi	R16, LOW(RAMEND)		; za�adowanie adresu ko�ca pami�ci[sta�a RAMEND - zdefiniowana w pliku m32def.inc z katalogu dependencies projektu](starszej jego cz��i) SRAM do R16
out	SPL, R16				; za�adowanie zawarto�ci rejestru R16 do SPH(starszej cz��i) rejestru kt�ry przechowuje tzw. wska�nik ko�ca stosu
ldi	R16, HIGH(RAMEND)		; za�adowanie (mlodszej czesci) adresu konca pamieci sram do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru kt�ry przechowuje wska�nik ko�ca stosu(m�odszej cz�ci)

in R16, DDRA				; wczytaj zawarto�� rejestru DDRA do rejestru R16
ori R16, 0b00000111			; wykonaj sum� logiczn� zawarto�ci rejestru R16 i warto�ci 00000111 (bin), wynik zapisz do R16, po tej oberacji R16.0=1, R16.1=1, R16.2=1
out DDRA, R16				; ustaw jako linie wej�ciowe piny [0, 1, 2] PA

main:						; program g��wny
	rcall setBits500		; wywo�aj procedur� ustawiaj�c� pierwsze trzy bity rejestru PORTA w ustawieniu dla op�nienia 500ms
	rcall delay250			; wywo�aj procedur� op�nienia
	rcall delay250			; wywo�aj procedur� op�nienia
	rcall setBits250		; wywo�aj procedur� ustawiaj�c� pierwsze trzy bity rejestru PORTA w ustawieniu dla op�nienia 250ms
	rcall delay250			; wywo�aj procedur� op�nienia
	rjmp main				; skocz na pocz�tek programu g��wnego

setBits250:					; ustaw bity rejestru PORTA dla op�nienia 250ms
	in R16, PINA			; wczytaj zawarto�� rejestru PINA do rejestru R16
	mov R17, R16			; kopiuj zawarto�� rejestru R16 do rejestru R17
	ori R17, 0b00001000		; wykonaj sum� logiczn� zawarto�ci rejestru R17 i warto�ci 00001000 (bin), wynik zapisz do R17, po tej oberacji R17.3=1
	cpse R16, r17			; por�wnaj rejestry R16 i R17, a je�li s� r�wne, to pomi� kolejn� instrukcj� (pomi� je�li PA.3=1)
	rjmp threeIsCleared		; skocz do etykiety
threeIsSet:					; wykonuje je�li PA.3=1
	ldi R16, 0b00000101		; za�aduj sta�� 00000101 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawarto�� rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sum� logiczn� na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=1, R17.2=1
	ldi R16, 0b11111101		; za�aduj sta�� 11111101 (bin) do rejestru R16
	and R17, R16			; wykonaj bitowy iloczyn na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.1=0
	out PORTA, R17			; zapisz zawarto�� rejestru R17 do rejestru PORTA, po tej operacji PA.0=1, PA.1=0, PA.2=1
	ret						; powr�� z podprogramu
threeIsCleared:				; wykonuje je�li PA.3=0
	ldi R16, 0b00000111		; za�aduj sta�� 00000111 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawarto�� rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sum� logiczn� na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=1, R17.1=1, R17.2=1
	out PORTA, R17			; zapisz zawarto�� rejestru R17 do rejestru PORTA, po tej operacji PA.0=1, PA.1=1, PA.2=1
	ret						; powr�� z podprogramu

setBits500:					; ustaw bity rejestru PORTA dla op�nienia 500ms
	ldi R16, 0b00000010		; za�aduj sta�� 00000010 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawarto�� rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sum� logiczn� na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.1=1
	ldi R16, 0b11111010		; za�aduj sta�� 11111010 (bin) do rejestru R16
	and R17, R16			; wykonaj bitowy iloczyn na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=0, R17.2=0
	out PORTA, R17			; zapisz zawarto�� rejestru R17 do rejestru PORTA, po tej operacji PA.0=0, PA.1=1, PA.2=0
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
