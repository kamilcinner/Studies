;
; cw5-z2.asm
;
; Created: 10/18/2020 3:57:55 AM
; Author : Kamil Cinner
;

.org 0						; wymuszenie pocz¹tku nastêpnych rozkazów od adresu 0x000
jmp RESET					; pod adresem 0x000 znajduje siê wektor przerwania inicjalizacyjnego
							; skok bezpoœredni do podprogramu obs³ugi tego przerwania

RESET:						; podprogram obs³ugi przerwania inicjalizacyjnego
	ldi R16, HIGH(RAMEND)	; inicjalizacja wskaŸnika stosu
	out SPH, R16
	ldi R16, LOW(RAMEND)
	out SPL, R16

	
	ldi R16, HIGH(2930)		; inicjalizacja rejestru ICR1, gdzie bêdzie ustawiona
	out ICR1H, R16			; maksymalna wartoœæ licznika, po której nast¹pi wyzerowanie
	ldi R16, LOW(2930)		; liczba 2930 * 1024 = 3000320 (1024 - ustawienie preskalera)
	out ICR1L, R16			; daje nam to w przybli¿eniu 3 sekundy


	ldi R16, HIGH(1954)		; inicjalizacja rejestru OCR1A, gdzie bêdzie ustawiona
	out OCR1AH, R16			; przejœciowa wartoœæ licznika, po której nast¹pi zmiana stanu na OC1A
	ldi R16, LOW(1954)		; liczba 1954 * 1024 = 2000896 (1024 - ustawienie preskalera)
	out OCR1AL, R16			; daje nam to w przybli¿eniu 2 sekundy

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

	jmp main				; skocz do programu g³ównego

main:						; program g³ówny
    rjmp main				; wróæ na pocz¹tek programu g³ównego