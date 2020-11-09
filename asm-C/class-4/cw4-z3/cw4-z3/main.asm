;
; cw4-z3.asm
;
; Created: 10/15/2020 11:25:04 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz�tku nast�pnych rozkaz�w od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje si� wektor przerwania inicjalizacyjnego
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje si� wektor przerwania zewn�trznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s�owa i st�d przesuni�cie w pami�ci)
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania

RESET:						; podprogram obs�ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wska�nika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16
	sei						; zezwolenie na obs�ug� przerwa�
	in R16, DDRA			; wczytaj rejestr DDRA do rejestru R16
	ori R16, 0b00000111		; ustaw R16.0-2=1
	out DDRA, R16			; ustaw piny [0, 1, 2] PA jako linie wyj�ciowe

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000001		; ustaw R16.0=1
	andi R16, 0b11111101	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'any logical change' dla przerwania INT0
							; czyli przerwanie zostanie wywo�ane gdy pin PD.3 zmieni sw�j stan (1 -> 0) lub (0 -> 1)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0

	jmp main				; skocz do programu g��wnego

EXT_INT0:					; podrpogram obs�ugi przerwania INT0
	cli						; zablokuj obs�ug� przerwa�
	push R17				; zabezpiecz zawarto�� rejestru R17 na stosie
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	ldi R16, 0				; za��duj warto�� 0 do rejestru R16
	bld R16, 0				; kopiuj flag� T z jerestru SREG do R16.0
	com R16					; neguj bity jerestru R16
	

	pop R17					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R17			; przywr�� zachowany rejestr SREG
	bst R16, 0				; ustaw flag� T rejestru SREG na podstawie wcze�niejszych operacji
	pop R16					; przywr�� zachowany rejestr R16
	pop R17					; przywr�� zachowany rejestr R17
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

main:						; program g��wny
	in R16, PORTA			; wczytaj rejestr PORTA do rejestru R16
	ori R16, 0b00000101		; ustaw R16.0=1, R16.2=1

	brts odd				; skocz je�li przerwanie nieparzyste
even:						; przerwanie parzyste
	andi R16, 0b11111101	; ustaw R16.1=0
	rjmp continue
odd:						; przerwanie nieparzyste
	ori R16, 0b00000010		; ustaw R16.1=1
continue:
	out PORTA, R16			; zapisz zawarto�� rejestru R16 w rejestrze PORTA
	rcall delay250			; wywo�aj procedur� op�nienia o 250ms
	in R16, PORTA			; wczytaj rejestr PORTA do rejestru R16
	andi R16, 0b11111010	; ustaw R16.0=0, R16.2=0
	ori R16, 0b00000010		; ustaw R16.1=1
	out PORTA, R16			; zapisz zawarto�� rejestru R16 w rejestrze PORTA
	rcall delay250			; wywo�aj procedur� op�nienia o 250ms
	rcall delay250			; wywo�aj procedur� op�nienia o 250ms
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
