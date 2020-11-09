;
; cw5-z3.asm
;
; Created: 10/18/2020 5:00:29 PM
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

	ldi R16, 0		; inicjalizacja rejestru ICR1, gdzie bêdzie ustawiona
	out ICR1H, R16			; maksymalna wartoœæ licznika, po której nast¹pi wyzerowanie
	ldi R16, 224		; liczba 224 * 1024 = 230000 (1024 - ustawienie preskalera)
	out ICR1L, R16			; daje nam to w przybli¿eniu 230ms

	ldi R16, 0		; inicjalizacja rejestru OCR1A, gdzie bêdzie ustawiona
	out OCR1AH, R16			; przejœciowa wartoœæ licznika, po której nast¹pi zmiana stanu na OC1A
	ldi R16, 195		; liczba 195 * 1024 = 200000 (1024 - ustawienie preskalera)
	out OCR1AL, R16			; daje nam to w przybli¿eniu 200ms

	sbi DDRD, 5				; ustawienie PD.5 jako linia wyjœciowa, dla OC1A

	sei						; zezwolenie na obs³ugê przerwañ

							; ustawienie trybu pracy 'Fast PWM' dla TIMER1
							; ustawienie jako wartoœæ maksymalna licznika rejestru ICR1
							; po jej osi¹gniêciu timer automatycznie zeruje siê
							; dodatkowo ustawienie trybu 'Set on compare match', który po zrównaniu
							; licznika timera z wartoœci¹ przejœciow¹ zapisan¹ w rejestrze OCR1A
							; ustawi OC1A=1, a po zrównaniu z wartoœci¹ maksymaln¹ ustawi OC1A=0
	in R16, TCCR1A			; wczytaj rejest TCCR1A do rejestru R16
	ori R16, 0b11000010		; ustaw R16.1=1, R16.6=1, R16.7=1
	andi R16, 0b11111110	; ustaw R16.0=0
	out TCCR1A, R16			; ustaw WGM10=0, WGM11=1, COM1A0=1, COM1A1=1

	in R16, TCCR1B			; wczytaj rejest TCCR1B do rejestru R16
	ori R16, 0b00011000		; ustaw R16.3-4=1
	out TCCR1B, R16			; ustaw WGM12=1, WGM13=1

	in R16, TCCR1B			; wczytaj rejestr TCCR1B do rejestru R16
	andi R16, 0b11111101	; ustaw R16.1=0
	ori R16, 0b00000101		; ustaw R16.0=1, R16.2=1
	out TCCR1B, R16			; ustaw preskaler Ÿród³a taktowania na 1/1024 (timer w³¹czony)

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo³ane gdy pin PD.2 zmieni swój stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0

	jmp main				; skocz do programu g³ównego

EXT_INT0:					; podprogram obs³ugi przerwania INT0
	cli						; zablokuj obs³ugê przerwañ
	push R22				; zabezpiecz zawartoœæ rejestru R22 na stosie
	push R21				; zabezpiecz zawartoœæ rejestru R21 na stosie
	push R20				; zabezpiecz zawartoœæ rejestru R20 na stosie
	push R19				; zabezpiecz zawartoœæ rejestru R19 na stosie
	push R18				; zabezpiecz zawartoœæ rejestru R18 na stosie
	push R17				; zabezpiecz zawartoœæ rejestru R17 na stosie
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	in R16, OCR1AL			; wczytaj m³odsz¹ czêœæ rejestru OCR1A do rejestru R16
	in R17, OCR1AH			; wczytaj starsz¹ czêœæ rejestru OCR1A do rejestru R17

	in R18, ICR1L			; wczytaj m³odsz¹ czêœæ rejestru ICR1 do rejestru R18
	in R19, ICR1H			; wczytaj starsz¹ czêœæ rejestru ICR1 do rejestru R19

	ldi R20, 9				; za³aduj wartoœæ 9 do rejestru R20
	add R16, R20			; dodaj zawartoœæ rejestru R20 do rejestru R16, wynik zapisz w R16
	
	mov R21, R16
	ldi R22, 0
	add R16, R20
	sub R18, R16

	brmi end				; jeœli wynik jest ujemny, to skocz na koniec podrpogramu
							; obs³ugi przerwania i nie aktualizuj OCR1A

fine:						; zaktualizuj wartoœæ OCR1A
	in R16, TCCR1B			; wy³¹cz timer (od³¹czenie Ÿród³a taktowania)
	andi R16, 0b11111000
	out TCCR1B, R16

	in R16, TCCR1A			; zresetowanie trybu pracy timera (docelowy tryb Normal)
	andi R16, 0b11111100
	out TCCR1A, R16
	in R16, TCCR1B
	andi R16, 0b11100111
	out TCCR1B, R16

	out OCR1AH, R22			; aktualizacja wartoœci poœredniej licznika timera
	out OCR1AL, R21

	in R16, TCCR1A			; przywrócenie trybu timera 'Fast PWM'
	ori R16, 0b00000010
	andi R16, 0b11111110
	out TCCR1A, R16
	in R16, TCCR1B
	ori R16, 0b00011000
	out TCCR1B, R16

	in R16, TCCR1B			; w³¹cz timer (pod³¹czenie Ÿród³a taktowania z preskalerem 1/1024)
	andi R16, 0b11111101
	ori R16, 0b00000101
	out TCCR1B, R16
end:						; zakoñczenie podprogramu obs³ugi przerwania
	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	pop R17					; przywróæ zachowany rejestr R17
	pop R18					; przywróæ zachowany rejestr R18
	pop R19					; przywróæ zachowany rejestr R19
	pop R20					; przywróæ zachowany rejestr R20
	pop R21					; przywróæ zachowany rejestr R21
	pop R22					; przywróæ zachowany rejestr R22
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

main:						; program g³ówny
	call EXT_INT0
    rjmp main				; wróæ na pocz¹tek programu g³ównego