;
; cw4-z2.asm
;
; Created: 10/15/2020 11:21:17 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz¹tku nastêpnych rozkazów od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje siê wektor przerwania inicjalizacyjnego
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje siê wektor przerwania zewnêtrznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s³owa i st¹d przesuniêcie w pamiêci)
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania
jmp EXT_INT1				; pod adresem 0x004 znajduje siê wektor przerwania zewnêtrznego INT1
							; (poprzednia instrukcja skoku zajmuje kolejne dwa s³owa i st¹d przesuniêcie w pamiêci)
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania

RESET:						; podprogram obs³ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wskaŸnika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16
	sei						; zezwolenie na obs³ugê przerwañ
	sbi DDRA, 0				; ustaw pin PA.0 jako linia wyjœciowa
	cbi PORTA, 0			; ustaw PA.0=0

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000110		; ustaw R16.1=1, R16.2=1
	andi R16, 0b11110110	; ustaw R16.0=0, R16.3=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo³ane gdy pin PD.2 zmieni swój stan z wysokiego na niski (1 -> 0)
							; ustaw tryb 'any logical change' dla INT1
							; czyli przerwanie zostanie wywo³ane gdy pin PD.3 zmieni swój stan (1 -> 0) lub (0 -> 1)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b11000000		; ustaw R16.6=1, R16.7=1
	out GICR, R16			; odblokuj przerwania INT0 oraz INT1

	jmp main				; skocz do programu g³ównego

EXT_INT0:					; podrpogram obs³ugi przerwania INT0
	cli						; zablokuj obs³ugê przerwañ
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	sbi PORTA, 0			; ustaw PA.0=1

	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

EXT_INT1:					; podrpogram obs³ugi przerwania INT1
	cli						; zablokuj obs³ugê przerwañ
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	cbi PORTA, 0			; ustaw PA.0=0

	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

main:						; program g³ówny
	jmp main				; wróæ na pocz¹tek programu g³ównego
