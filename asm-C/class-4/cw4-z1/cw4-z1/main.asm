;
; cw4-z1.asm
;
; Created: 10/15/2020 10:27:28 AM
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
	ser R16					; ustaw wszystkie bity rejestru R16
	out DDRA, R16			; ustaw wszystkie piny PA jako linie wyj�ciowe
	out DDRB, R16			; ustaw wszystkie piny PB jako linie wyj�ciowe
	ldi R16, 0b11110000		; ustaw 4 najstarsze i wyzeruj 4 najm�odsze bity PA
	out PORTA, R16

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo�ane gdy pin PD.2 zmieni sw�j stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0

	jmp main				; skocz do programu g��wnego

EXT_INT0:					; podrpogram obs�ugi przerwania INT0
	cli						; zablokuj obs�ug� przerwa�
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	in R16, PORTA			; wczytaj reejstr PORTA do rejestru R16
	com R16					; neguj bity rejestru R16
	out PORTA, R16			; zapisz zawarto�� rejestru R16 w rejestrze PORTA

	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

main:						; program g��wny
	ldi R16, 0				; wczytaj warto�� 0 do rejestru R16
	ldi R17, -2				; wczytaj warto�� -2 do rejestru R17
	add	R17, R16			; dodaj warto�� 0 do warto�ci -2
	rcall delayNop256		; wywo��j podprogram op�niaj�cy
	brbs 4, negative		; skocz do etykiety je�li wynik by� ujemny
nonNegative:
	ldi R16, 0b01010101		; wczytaj warto�� 01010101 (bin) do rejestru R16 (wynik nieujemny)
	rjmp continue			; pomi� ustawianie warto�ci dla wyniku ujemnego
negative:
	ldi R16, 0b10101010		; wczytaj warto�� 10101010 (bin) do rejestru R16 (wynik ujemny)
continue:
	out PORTB, R16			; zapisz warto�� rejestru R16 w rejestrze PORTB
	jmp main				; wr�� na pocz�tek programu g��wnego

delayNop256:				; podprogram sk�adaj�cy si� z 256 instrukcji nop
	nop						; nie r�b nic przez 1 cykl
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	ret							; powr�� z podprogramu
