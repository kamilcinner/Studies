;
; cw5-z1.asm
;
; Created: 10/18/2020 12:19:05 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz¹tku nastêpnych rozkazów od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje siê wektor przerwania inicjalizacyjnego
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje siê wektor przerwania zewnêtrznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s³owa i st¹d przesuniêcie w pamiêci)
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania

.org 0x00E					; wymuszenie pocz¹tku nastêpnych rozkazów od adresu 0x00E
							; pod adresem 0x00E znajduje siê wektor przerwania TIMER1 porównania rejestru OCR1A
jmp TIMER1_COMPA			; skok bezpoœredni do podprogramu obs³ugi tego przerwania

RESET:						; podprogram obs³ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wskaŸnika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16

	ldi R16, HIGH(1465)		; inicjalizacja rejestru OCR1A, gdzie bêdzie ustawiona
	out OCR1AH, R16			; maksymalna wartoœæ licznika, po której nast¹pi wyzerowanie
	ldi R16, LOW(1465)		; liczba 1465 * 1024 = 1500160 (1024 - ustawienie preskalera)
	out OCR1AL, R16			; daje nam to w przybli¿eniu 1,5 sekundy

	sei						; zezwolenie na obs³ugê przerwañ

							; ustawienie trybu pracy CTC dla TIMER1
							; w trybie tym timer automatycznie zeruje siê po osi¹gniêciu
							; maksymalnej wartoœci licznika
	in R16, TCCR1A			; wczytaj rejest TCCR1A do rejestru R16
	andi R16, 0b11111100	; ustaw R16.0=0, R16.1=0
	out TCCR1A, R16			; ustaw bity WGM10=0, WGM11=0

	in R16, TCCR1B			; wczytaj rejest TCCR1B do rejestru R16
	ori R16, 0b00001000		; ustaw R16.3=1
	andi R16, 0b11101111	; ustaw R16.4=0
	out TCCR1B, R16			; ustaw bity WGM12=1 WGM13=0

	in R16, TIMSK			; wczytaj rejest TIMSK do rejestru R16
	ori R16, 0b00010000		; ustaw R16.4=1
	out TIMSK, R16			; ustaw bit OCIE1A=1 (w³¹czenie aktywowania przerwania w momencie zrównania
							; licznika TIMER1 z maksymaln¹ wartoœci¹ zapisan¹ w OCR1A

	sbi DDRA, 0				; ustaw PA.0 jako linia wyjœciowa

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo³ane gdy pin PD.2 zmieni swój stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0
	call EXT_INT0
	jmp main				; skocz do programu g³ównego

EXT_INT0:					; podprogram obs³ugi przerwania INT0
	cli						; zablokuj obs³ugê przerwañ
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	sbi PORTA, 0			; ustaw PA.0=1

	in R16, TCCR1B			; wczytaj rejestr TCCR1B do rejestru R16
	andi R16, 0b11111101	; ustaw R16.1=0
	ori R16, 0b00000101		; ustaw R16.0=1, R16.2=1
	out TCCR1B, R16			; ustaw preskaler Ÿród³a taktowania na 1/1024 (timer w³¹czony)

	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

TIMER1_COMPA:				; podprogram obs³ugi przerwania TIMER1 COMPA
	cli						; zablokuj obs³ugê przerwañ
	push R16				; zabezpiecz zawartoœæ rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawartoœæ rejestru SREG na stosie

	cbi PORTA, 0			; ustaw PA.0=0
	
	in R16, TCCR1B			; wczytaj rejestr TCCR1B do rejestru R16
	andi R16, 0b11111000	; ustaw R16.0-2=0
	out TCCR1B, R16			; od³¹cz Ÿród³o taktowania TIMER1 (timer zostaje zastopowany)

	pop R16					; zdejmij ze stosu pierwotn¹ wartoœæ SREG i zapisz w R16
	out SREG, R16			; przywróæ zachowany rejestr SREG
	pop R16					; przywróæ zachowany rejestr R16
	reti					; powróæ z podprogramu obs³ugi przerwania INT0
							; jednoczeœnie ustawiaj¹c flagê zezwolenia na przerwania w SREG

main:						; program g³ówny
    rjmp main				; wróæ na pocz¹tek programu g³ównego
