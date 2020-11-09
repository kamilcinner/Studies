;
; cw4-z2.asm
;
; Created: 10/15/2020 11:21:17 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz�tku nast�pnych rozkaz�w od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje si� wektor przerwania inicjalizacyjnego
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje si� wektor przerwania zewn�trznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s�owa i st�d przesuni�cie w pami�ci)
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania
jmp EXT_INT1				; pod adresem 0x004 znajduje si� wektor przerwania zewn�trznego INT1
							; (poprzednia instrukcja skoku zajmuje kolejne dwa s�owa i st�d przesuni�cie w pami�ci)
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania

RESET:						; podprogram obs�ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wska�nika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16
	sei						; zezwolenie na obs�ug� przerwa�
	sbi DDRA, 0				; ustaw pin PA.0 jako linia wyj�ciowa
	cbi PORTA, 0			; ustaw PA.0=0

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000110		; ustaw R16.1=1, R16.2=1
	andi R16, 0b11110110	; ustaw R16.0=0, R16.3=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo�ane gdy pin PD.2 zmieni sw�j stan z wysokiego na niski (1 -> 0)
							; ustaw tryb 'any logical change' dla INT1
							; czyli przerwanie zostanie wywo�ane gdy pin PD.3 zmieni sw�j stan (1 -> 0) lub (0 -> 1)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b11000000		; ustaw R16.6=1, R16.7=1
	out GICR, R16			; odblokuj przerwania INT0 oraz INT1

	jmp main				; skocz do programu g��wnego

EXT_INT0:					; podrpogram obs�ugi przerwania INT0
	cli						; zablokuj obs�ug� przerwa�
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	sbi PORTA, 0			; ustaw PA.0=1

	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

EXT_INT1:					; podrpogram obs�ugi przerwania INT1
	cli						; zablokuj obs�ug� przerwa�
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	cbi PORTA, 0			; ustaw PA.0=0

	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

main:						; program g��wny
	jmp main				; wr�� na pocz�tek programu g��wnego
