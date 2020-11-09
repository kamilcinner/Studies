;
; cw3-z2.asm
;
; Created: 10/12/2020 7:13:05 PM
; Author : Kamil Cinner
;

; inicjalizacja wska�nika stosu
ldi	R16, LOW(RAMEND)		; za�adowanie adresu ko�ca pami�ci[sta�a RAMEND - zdefiniowana w pliku m32def.inc w katalogu dependencies projektu](starszej jego cz�ci) SRAM do R16
out	SPL, R16				; za�adowanie zawarto�ci rejestru R16 do SPH(starszej cz��i) rejestru kt�ry przechowuje tzw. wska�nik ko�ca stosu
ldi	R16, HIGH(RAMEND)		; za�adowanie (m�odszej czesci) adresu ko�ca pamieci SRAM do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru kt�ry przechowuje wska�nik ko�ca stosu(m�odszej czesci)

ser R16						; ustaw wszystkie bity w rejestrze R16
out DDRA, R16				; ustaw jako linie wyj�ciowe wszystkie piny PA

ldi R16, 0b00000001			; za�aduj sta�� 00000001 (bin) do rejestru R16

main:						; program g��wny
	out PORTA, R16			; zapisz zawarto�� rejestru R16 do rejestru PORTA
	rcall delay4_9			; wywo�aj procedur� op�nienia
	in R16, PINA			; wczytaj zawarto�� rejestru PINA do rejestru R16
	lsl R16					; logiczne przesuni�cie w lewo na rejestrze R16

; sprawd� czy nast�pi�o przeniesienie i je�li tak to za�aduj warto�� pocz�tkow� 00000001 (bin) do rejestru R16
	in R17, SREG			; wczytaj zawarto�� rejestru SREG do rejestru R17
	mov R18, R17			; kopiuj zawarto�� rejestru R17 do rejestru R18
	andi R18, 0b11111110	; wykonaj bitowy iloczyn zawarto�ci rejestru R18 i warto�ci 11111110 (bin), wynik zapisz do R18, po tej operacji R18.0=0
	cpse R17, R18			; por�wnaj rejestry R17 i R18, a je�li s� r�wne, to pomi� kolejn� instrukcj� (pomija je�li flaga przeniesienia w SREG jest nie ustawiona)
	ldi R16, 0b00000001		; za�aduj sta�� 00000001 (bin) do rejestru R16
	rjmp main				; skocz na pocz�tek programu g��wnego

delay4_9:					; p�tla op�niaj�ca o 4,9ms (4 900 cykli)
; 4899 cykli:
			ldi  R17, $17	; za�adowanie warto�ci $17 (hex) do rejestru R17
WGLOOP0:	ldi  R18, $46	; za�adowanie warto�ci $46 (hex) do rejestru R18
WGLOOP1:	dec  R18		; zmniejsz warto�� rejestru R18 o 1, je�eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP1	; je�li wynik ostatniej operacji dekrementowania jest r�ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP1
			dec  R17		; zmniejsz warto�� rejestru R17 o 1, je�eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP0	; je�li wynik ostatniej operacji dekrementowania jest r�ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP0
; 1 cykl:
			nop				; nie r�b nic przez 1 cykl
			ret				; wro� z podprogramu
