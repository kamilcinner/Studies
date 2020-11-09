; Autor: Kamil Cinner
;

; inicjalizacja wskaŸnika stosu
ldi	R16, LOW(RAMEND)		; za³adowanie adresu koñca pamiêci[sta³a RAMEND - zdefiniowana w pliku m32def.inc z katalogu dependencies projektu](starszej jego czêœæi) SRAM do R16
out	SPL, R16				; za³adowanie zawartoœci rejestru R16 do SPH(starszej czêœæi) rejestru który przechowuje tzw. wskaŸnik koñca stosu
ldi	R16, HIGH(RAMEND)		; za³adowanie (mlodszej czesci) adresu konca pamieci SRAM do R16
out	SPH, R16				; przepisanie R16 do SPL - rejestru który przechowuje wska¿nik koñca stosu(m³odszej czêœci)

sbi DDRA, 0					; ustaw pin PA.0 jako linia wyjœciowa
sbi DDRA, 1					; ustaw pin PA.1 jako linia wyjœciowa
sbi DDRA, 2					; ustaw pin PA.2 jako linia wyjœciowa

main:						; program g³ówny
    rcall setBits500		; wywo³aj procedurê ustawiaj¹c¹ pierwsze trzy bity rejestru PORTA w ustawieniu dla opóŸnienia 500ms
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rcall setBits250		; wywo³aj procedurê ustawiaj¹c¹ pierwsze trzy bity rejestru PORTA w ustawieniu dla opóŸnienia 250ms
	rcall delay250			; wywo³aj procedurê opóŸnienia
	rjmp main				; wróæ na pocz¹tek programu g³ównego

setBits500:					; ustaw bity rejestru PORTA dla opóŸnienia 500ms
	cbi PORTA, 0			; ustaw PA.0=0
	sbi PORTA, 1			; ustaw PA.1=1
	cbi PORTA, 2			; ustaw PA.2=0
	ret						; powróæ z podprogramu

setBits250:					; ustaw bity rejestru PORTA dla opóŸnienia 250ms
	sbi PORTA, 0			; ustaw PA.0=1

; ustaw PA.1 w zale¿noœci od PA.3
	sbis PINA, 3			; jeœli PA.3=1, to pomiñ nastêpn¹ instrukcjê
	sbi PORTA, 1			; ustaw PA.1=1
	sbic PINA, 3			; jeœli PA.3=0, to pomiñ nastêpn¹ instrukcjê
	cbi PORTA, 1			; ustaw PA.1=0

	sbi PORTA, 2			; ustaw PA.2=1
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
