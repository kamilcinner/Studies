;
; cw3-z1.asm
;
; Created: 10/12/2020 6:30:37 PM
; Author : Kamil Cinner
;

; inicjalizacja wskaŸnika stosu
ldi	R16, LOW(RAMEND)		; za³adowanie adresu koñca pamiêci[sta³a RAMEND - zdefiniowana w pliku m32def.inc z katalogu dependencies projektu](starszej jego czêœæi) SRAM do R16
out	SPL, R16				; za³adowanie zawartoœci rejestru R16 do SPH(starszej czêœæi) rejestru który przechowuje tzw. wskaŸnik koñca stosu
ldi	R16, HIGH(RAMEND)		; za³adowanie (mlodszej czesci) adresu konca pamieci sram do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru który przechowuje wska¿nik koñca stosu(m³odszej czêœci)

in R16, DDRA				; wczytaj zawartoœæ rejestru DDRA do rejestru R16
ori R16, 0b00000111			; wykonaj sumê logiczn¹ zawartoœci rejestru R16 i wartoœci 00000111 (bin), wynik zapisz do R16, po tej oberacji R16.0=1, R16.1=1, R16.2=1
out DDRA, R16				; ustaw jako linie wejœciowe piny [0, 1, 2] PA

main:						; program g³ówny
	rcall setBits500		; wywo³aj procedurê ustawiaj¹c¹ pierwsze trzy bity rejestru PORTA w ustawieniu dla opóŸnienia 500ms
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rcall setBits250		; wywo³aj procedurê ustawiaj¹c¹ pierwsze trzy bity rejestru PORTA w ustawieniu dla opóŸnienia 250ms
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rjmp main				; skocz na pocz¹tek programu g³ównego

setBits250:					; ustaw bity rejestru PORTA dla opóŸnienia 250ms
	in R16, PINA			; wczytaj zawartoœæ rejestru PINA do rejestru R16
	mov R17, R16			; kopiuj zawartoœæ rejestru R16 do rejestru R17
	ori R17, 0b00001000		; wykonaj sumê logiczn¹ zawartoœci rejestru R17 i wartoœci 00001000 (bin), wynik zapisz do R17, po tej oberacji R17.3=1
	cpse R16, r17			; porównaj rejestry R16 i R17, a jeœli s¹ równe, to pomiñ kolejn¹ instrukcjê (pomiñ jeœli PA.3=1)
	rjmp threeIsCleared		; skocz do etykiety
threeIsSet:					; wykonuje jeœli PA.3=1
	ldi R16, 0b00000101		; za³aduj sta³¹ 00000101 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawartoœæ rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sumê logiczn¹ na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=1, R17.2=1
	ldi R16, 0b11111101		; za³aduj sta³¹ 11111101 (bin) do rejestru R16
	and R17, R16			; wykonaj bitowy iloczyn na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.1=0
	out PORTA, R17			; zapisz zawartoœæ rejestru R17 do rejestru PORTA, po tej operacji PA.0=1, PA.1=0, PA.2=1
	ret						; powróæ z podprogramu
threeIsCleared:				; wykonuje jeœli PA.3=0
	ldi R16, 0b00000111		; za³aduj sta³¹ 00000111 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawartoœæ rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sumê logiczn¹ na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=1, R17.1=1, R17.2=1
	out PORTA, R17			; zapisz zawartoœæ rejestru R17 do rejestru PORTA, po tej operacji PA.0=1, PA.1=1, PA.2=1
	ret						; powróæ z podprogramu

setBits500:					; ustaw bity rejestru PORTA dla opóŸnienia 500ms
	ldi R16, 0b00000010		; za³aduj sta³¹ 00000010 (bin) do rejestru R16
	in R17, PINA			; wczytaj zawartoœæ rejestru PINA do rejestru R17
	or R17, R16				; wykonaj sumê logiczn¹ na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.1=1
	ldi R16, 0b11111010		; za³aduj sta³¹ 11111010 (bin) do rejestru R16
	and R17, R16			; wykonaj bitowy iloczyn na rejestrach R17 i R16, wynik zapisz do R17, po tej operacji R17.0=0, R17.2=0
	out PORTA, R17			; zapisz zawartoœæ rejestru R17 do rejestru PORTA, po tej operacji PA.0=0, PA.1=1, PA.2=0
	ret						; powróæ z podprogramu

delay250:					; pêtla opóŸniaj¹ca o 250ms (250 000 cykli)
; 249 999 cykli:
			ldi  R17, $A7	; za³adowanie wartoœci $A7 (hex) do rejestru R17
WGLOOP0:	ldi  R18, $02	; za³adowanie wartoœci $02 (hex) do rejestru R18
WGLOOP1:	ldi  R19, $F8	; za³adowanie wartoœci $F8 (hex) do rejestru R19
WGLOOP2:	dec  R19		; zmniejsz wartoœæ rejestru R19 o 1, je¿eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP2	; jeœli wynik ostatniej operacji dekrementowania jest ró¿ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP2
			dec  R18		; zmniejsz wartoœæ rejestru R18 o 1, je¿eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP1	; jeœli wynik ostatniej operacji dekrementowania jest ró¿ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP1
			dec  R17		; zmniejsz wartoœæ rejestru R17 o 1, je¿eli wynikiem jest zero, to zostaje ustawiona flaga ZERA w SREG
			brne WGLOOP0	; jeœli wynik ostatniej operacji dekrementowania jest ró¿ny od zera (flaga ZERA w SREG jest ustawiona), to skocz do etykiety WGLOOP0
; 1 cykl:
			nop				; nie rób nic przez 1 cykl
			ret				; wroæ z podprogramu
