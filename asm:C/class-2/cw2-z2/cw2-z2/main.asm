; Autor: Kamil Cinner
;

; inicjalizacja wskaŸnika stosu
ldi R16, HIGH(RAMEND)		; za³adowanie adresu koñca pamiêci[sta³a RAMEND - zdefiniowana w pliku m32def.inc w katalogu dependencies projektu](starszej jego czêœci) SRAM do R16
out SPH, R16				; za³adowanie zawartoœci rejestru R16 do SPH(starszej czêœi) rejestru który przechowuje tzw. wskaŸnik koñca stosu
ldi R16, LOW(RAMEND)		; za³adowanie (m³odszej czêœci) adresu konña pamiêci SRAM do R16
out SPL, R16				; przepisanie R16 do SPL - rejestru który przechowuje wskaŸnik koñca stosu(m³odszej czêœci)

sbi DDRA, 0					; ustawienie pinu PA.0 jako linia wyjœciowa

main:						; program g³ówny
    sbi PORTA, 0			; jeœli PA.0=1, to pomiñ nastêpn¹ instrukcjê
    rcall delay250			; wywo³aj podprogram opóŸniaj¹cy o 250ms (adresowanie wzglêdne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w porównaniu do instrukcji call)

	cbi PORTA, 0
	rcall delay250			; wywo³aj podprogram opóŸniaj¹cy o 250ms (adresowanie wzglêdne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w porównaniu do instrukcji call)
	rcall delay250			; wywo³aj podprogram opóŸniaj¹cy o 250ms (adresowanie wzglêdne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w porównaniu do instrukcji call)

    rjmp main				; wróæ na pocz¹tek programu g³ównego

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

