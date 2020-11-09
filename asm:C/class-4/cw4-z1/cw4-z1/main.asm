;
; cw4-z1.asm
;
; Created: 10/15/2020 10:27:28 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz¹tku nastêpnych rozkazów od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje siê wektor przerwania inicjalizacyjnego
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje siê wektor przerwania zewnêtrznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s³owa i st¹d przesuniêcie w pamiêci)
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania

RESET:						; podprogram obs³ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wskaŸnika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16
	sei						; zezwolenie na obs³ugê przerwañ
	ser R16					; ustaw wszystkie bity rejestru R16
	out DDRA, R16			; ustaw wszystkie piny PA jako linie wyjœciowe
	out DDRB, R16			; ustaw wszystkie piny PB jako linie wyjœciowe
	ldi R16, 0b11110000		; ustaw 4 najstarsze i wyzeruj 4 najm³odsze bity PA
	out PORTA, R16

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo³ane gdy pin PD.2 zmieni swój stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0

	jmp main				; skocz do programu g³ównego

EXT_INT0:					; podrpogram obs³ugi przerwania INT0
	cli						; zablokuj obs³ugê przerwañ
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	in R16, PORTA			; wczytaj reejstr PORTA do rejestru R16
	com R16					; neguj bity rejestru R16
	out PORTA, R16			; zapisz zawartoœæ rejestru R16 w rejestrze PORTA

	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

main:						; program g³ówny
	ldi R16, 0				; wczytaj wartoœæ 0 do rejestru R16
	ldi R17, -2				; wczytaj wartoœæ -2 do rejestru R17
	add	R17, R16			; dodaj wartoœæ 0 do wartoœci -2
	rcall delayNop256		; wywo³¹j podprogram opóŸniaj¹cy
	brbs 4, negative		; skocz do etykiety jeœli wynik by³ ujemny
nonNegative:
	ldi R16, 0b01010101		; wczytaj wartoœæ 01010101 (bin) do rejestru R16 (wynik nieujemny)
	rjmp continue			; pomiñ ustawianie wartoœci dla wyniku ujemnego
negative:
	ldi R16, 0b10101010		; wczytaj wartoœæ 10101010 (bin) do rejestru R16 (wynik ujemny)
continue:
	out PORTB, R16			; zapisz wartoœæ rejestru R16 w rejestrze PORTB
	jmp main				; wróæ na pocz¹tek programu g³ównego

delayNop256:				; podprogram sk³adaj¹cy siê z 256 instrukcji nop
	nop						; nie rób nic przez 1 cykl
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
	ret							; powróæ z podprogramu
