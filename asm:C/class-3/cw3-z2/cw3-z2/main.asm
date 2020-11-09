;
; cw3-z2.asm
;
; Created: 10/12/2020 7:13:05 PM
; Author : Kamil Cinner
;

; inicjalizacja wskaŸnika stosu
ldi	R16, LOW(RAMEND)		; za³adowanie adresu koñca pamiêci[sta³a RAMEND - zdefiniowana w pliku m32def.inc w katalogu dependencies projektu](starszej jego czêœci) SRAM do R16
out	SPL, R16				; za³adowanie zawartoœci rejestru R16 do SPH(starszej czêœæi) rejestru który przechowuje tzw. wskaŸnik koñca stosu
ldi	R16, HIGH(RAMEND)		; za³adowanie (m³odszej czesci) adresu koñca pamieci SRAM do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru który przechowuje wska¿nik koñca stosu(m³odszej czesci)

ser R16						; ustaw wszystkie bity w rejestrze R16
out DDRA, R16				; ustaw jako linie wyjœciowe wszystkie piny PA

ldi R16, 0b00000001			; za³aduj sta³¹ 00000001 (bin) do rejestru R16

main:						; program g³ówny
	out PORTA, R16			; zapisz zawartoœæ rejestru R16 do rejestru PORTA
	rcall delay4_9			; wywo³aj procedurê opóŸnienia
	in R16, PINA			; wczytaj zawartoœæ rejestru PINA do rejestru R16
	lsl R16					; logiczne przesuniêcie w lewo na rejestrze R16

; sprawdŸ czy nast¹pi³o przeniesienie i jeœli tak to za³aduj wartoœæ pocz¹tkow¹ 00000001 (bin) do rejestru R16
	in R17, SREG			; wczytaj zawartoœæ rejestru SREG do rejestru R17
	mov R18, R17			; kopiuj zawartoœæ rejestru R17 do rejestru R18
	andi R18, 0b11111110	; wykonaj bitowy iloczyn zawartoœci rejestru R18 i wartoœci 11111110 (bin), wynik zapisz do R18, po tej operacji R18.0=0
	cpse R17, R18			; porównaj rejestry R17 i R18, a jeœli s¹ równe, to pomiñ kolejn¹ instrukcjê (pomija jeœli flaga przeniesienia w SREG jest nie ustawiona)
	ldi R16, 0b00000001		; za³aduj sta³¹ 00000001 (bin) do rejestru R16
	rjmp main				; skocz na pocz¹tek programu g³ównego

delay4_9:					; pêtla opóŸniaj¹ca o 4,9ms (4 900 cykli)
; 4899 cykli:
			ldi  R17, $17	; za³adowanie wartoœci $17 (hex) do rejestru R17
WGLOOP0:	ldi  R18, $46	; za³adowanie wartoœci $46 (hex) do rejestru R18
WGLOOP1:	dec  R18		; zmniejsz wartoœæ rejestru R18 o 1, je¿eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP1	; jeœli wynik ostatniej operacji dekrementowania jest ró¿ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP1
			dec  R17		; zmniejsz wartoœæ rejestru R17 o 1, je¿eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP0	; jeœli wynik ostatniej operacji dekrementowania jest ró¿ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP0
; 1 cykl:
			nop				; nie rób nic przez 1 cykl
			ret				; wroæ z podprogramu
