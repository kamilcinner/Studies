;
; cw5-z1.asm
;
; Created: 10/18/2020 12:19:05 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz�tku nast�pnych rozkaz�w od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje si� wektor przerwania inicjalizacyjnego
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania
jmp EXT_INT0				; pod adresem 0x002 znajduje si� wektor przerwania zewn�trznego INT0
							; (poprzednia instrukcja skoku zajmuje dwa s�owa i st�d przesuni�cie w pami�ci)
							; skok bezpo�redni do podprogramu obs�ugi tego przerwania

.org 0x00E					; wymuszenie pocz�tku nast�pnych rozkaz�w od adresu 0x00E
							; pod adresem 0x00E znajduje si� wektor przerwania TIMER1 por�wnania rejestru OCR1A
jmp TIMER1_COMPA			; skok bezpo�redni do podprogramu obs�ugi tego przerwania

RESET:						; podprogram obs�ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wska�nika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16

	ldi R16, HIGH(1465)		; inicjalizacja rejestru OCR1A, gdzie b�dzie ustawiona
	out OCR1AH, R16			; maksymalna warto�� licznika, po kt�rej nast�pi wyzerowanie
	ldi R16, LOW(1465)		; liczba 1465 * 1024 = 1500160 (1024 - ustawienie preskalera)
	out OCR1AL, R16			; daje nam to w przybli�eniu 1,5 sekundy

	sei						; zezwolenie na obs�ug� przerwa�

							; ustawienie trybu pracy CTC dla TIMER1
							; w trybie tym timer automatycznie zeruje si� po osi�gni�ciu
							; maksymalnej warto�ci licznika
	in R16, TCCR1A			; wczytaj rejest TCCR1A do rejestru R16
	andi R16, 0b11111100	; ustaw R16.0=0, R16.1=0
	out TCCR1A, R16			; ustaw bity WGM10=0, WGM11=0

	in R16, TCCR1B			; wczytaj rejest TCCR1B do rejestru R16
	ori R16, 0b00001000		; ustaw R16.3=1
	andi R16, 0b11101111	; ustaw R16.4=0
	out TCCR1B, R16			; ustaw bity WGM12=1 WGM13=0

	in R16, TIMSK			; wczytaj rejest TIMSK do rejestru R16
	ori R16, 0b00010000		; ustaw R16.4=1
	out TIMSK, R16			; ustaw bit OCIE1A=1 (w��czenie aktywowania przerwania w momencie zr�wnania
							; licznika TIMER1 z maksymaln� warto�ci� zapisan� w OCR1A

	sbi DDRA, 0				; ustaw PA.0 jako linia wyj�ciowa

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo�ane gdy pin PD.2 zmieni sw�j stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0
	call EXT_INT0
	jmp main				; skocz do programu g��wnego

EXT_INT0:					; podprogram obs�ugi przerwania INT0
	cli						; zablokuj obs�ug� przerwa�
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	sbi PORTA, 0			; ustaw PA.0=1

	in R16, TCCR1B			; wczytaj rejestr TCCR1B do rejestru R16
	andi R16, 0b11111101	; ustaw R16.1=0
	ori R16, 0b00000101		; ustaw R16.0=1, R16.2=1
	out TCCR1B, R16			; ustaw preskaler �r�d�a taktowania na 1/1024 (timer w��czony)

	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

TIMER1_COMPA:				; podprogram obs�ugi przerwania TIMER1 COMPA
	cli						; zablokuj obs�ug� przerwa�
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

	cbi PORTA, 0			; ustaw PA.0=0
	
	in R16, TCCR1B			; wczytaj rejestr TCCR1B do rejestru R16
	andi R16, 0b11111000	; ustaw R16.0-2=0
	out TCCR1B, R16			; od��cz �r�d�o taktowania TIMER1 (timer zostaje zastopowany)

	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

main:						; program g��wny
    rjmp main				; wr�� na pocz�tek programu g��wnego
