; Autor: Kamil Cinner
;

; inicjalizacja wska�nika stosu
ldi R16, HIGH(RAMEND)		; za�adowanie adresu ko�ca pami�ci[sta�a RAMEND - zdefiniowana w pliku m32def.inc w katalogu dependencies projektu](starszej jego cz�ci) SRAM do R16
out SPH, R16				; za�adowanie zawarto�ci rejestru R16 do SPH(starszej cz�i) rejestru kt�ry przechowuje tzw. wska�nik ko�ca stosu
ldi R16, LOW(RAMEND)		; za�adowanie (m�odszej cz�ci) adresu kon�a pami�ci SRAM do R16
out SPL, R16				; przepisanie R16 do SPL - rejestru kt�ry przechowuje wska�nik ko�ca stosu(m�odszej cz�ci)

sbi DDRA, 0					; ustawienie pinu PA.0 jako linia wyj�ciowa

main:						; program g��wny
    sbi PORTA, 0			; je�li PA.0=1, to pomi� nast�pn� instrukcj�
    rcall delay250			; wywo�aj podprogram op�niaj�cy o 250ms (adresowanie wzgl�dne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w por�wnaniu do instrukcji call)

	cbi PORTA, 0
	rcall delay250			; wywo�aj podprogram op�niaj�cy o 250ms (adresowanie wzgl�dne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w por�wnaniu do instrukcji call)
	rcall delay250			; wywo�aj podprogram op�niaj�cy o 250ms (adresowanie wzgl�dne, w pozytywnym przypadku instrukcja zajmnie 1 cykl mniej w por�wnaniu do instrukcji call)

    rjmp main				; wr�� na pocz�tek programu g��wnego

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

