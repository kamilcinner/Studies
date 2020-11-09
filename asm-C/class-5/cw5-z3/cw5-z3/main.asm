;
; cw5-z3.asm
;
; Created: 10/18/2020 5:00:29 PM
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

	ldi R16, HIGH(2930)		; inicjalizacja rejestru ICR1, gdzie b�dzie ustawiona
	out ICR1H, R16			; maksymalna warto�� licznika, po kt�rej nast�pi wyzerowanie
	ldi R16, LOW(2930)		; liczba 2930 * 1024 = 3000320 (1024 - ustawienie preskalera)
	out ICR1L, R16			; daje nam to w przybli�eniu 3 sekundy

	ldi R16, HIGH(1954)		; inicjalizacja rejestru OCR1A, gdzie b�dzie ustawiona
	out OCR1AH, R16			; przej�ciowa warto�� licznika, po kt�rej nast�pi zmiana stanu na OC1A
	ldi R16, LOW(1954)		; liczba 1954 * 1024 = 2000896 (1024 - ustawienie preskalera)
	out OCR1AL, R16			; daje nam to w przybli�eniu 2 sekundy

	sbi DDRD, 5				; ustawienie PD.5 jako linia wyj�ciowa, dla OC1A

	sei						; zezwolenie na obs�ug� przerwa�

							; ustawienie trybu pracy 'Fast PWM' dla TIMER1
							; ustawienie jako warto�� maksymalna licznika rejestru ICR1
							; po jej osi�gni�ciu timer automatycznie zeruje si�
							; dodatkowo ustawienie trybu 'Set on compare match', kt�ry po zr�wnaniu
							; licznika timera z warto�ci� przej�ciow� zapisan� w rejestrze OCR1A
							; ustawi OC1A=1, a po zr�wnaniu z warto�ci� maksymaln� ustawi OC1A=0
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
	out TCCR1B, R16			; ustaw preskaler �r�d�a taktowania na 1/1024 (timer w��czony)

	in R16, MCUCR			; wczytaj rejestr MCUCR do rejestru R16
	ori R16, 0b00000010		; ustaw R16.1=1
	andi R16, 0b11111110	; ustaw R16.1=0
	out MCUCR, R16			; ustaw tryb 'falling edge' dla przerwania INT0
							; czyli przerwanie zostanie wywo�ane gdy pin PD.2 zmieni sw�j stan z wysokiego na niski (1 -> 0)

	in R16, GICR			; wczytaj rejestr GICR do rejestru R16
	ori R16, 0b01000000		; ustaw R16.6=1
	out GICR, R16			; odblokuj przerwanie INT0

	jmp main				; skocz do programu g��wnego

EXT_INT0:					; podprogram obs�ugi przerwania INT0
	cli						; zablokuj obs�ug� przerwa�
	push R22				; zabezpiecz zawarto�� rejestru R22 na stosie
	push R21				; zabezpiecz zawarto�� rejestru R21 na stosie
	push R20				; zabezpiecz zawarto�� rejestru R20 na stosie
	push R19				; zabezpiecz zawarto�� rejestru R19 na stosie
	push R18				; zabezpiecz zawarto�� rejestru R18 na stosie
	push R17				; zabezpiecz zawarto�� rejestru R17 na stosie
	push R16				; zabezpiecz zawarto�� rejestru R16 na stosie
	in R16, SREG			; wczytaj rejestr SREG do rejestru R16
	push R16				; zabezpiecz zawarto�� rejestru SREG na stosie

							; ---
							; wczytaj warto�� po�redni� licznika timera i dodaj do niej 100ms
							; 97 * 1024 = 99328, czyli w przybli�eniu 100ms
							; wynik zapisz w R17_R16
							; ---
	in R16, OCR1AL			; wczytaj m�odsz� cz�� rejestru OCR1A do rejestru R16
	in R17, OCR1AH			; wczytaj starsz� cz�� rejestru OCR1A do rejestru R17
	ldi R20, 97				; za�aduj warto�� 97 do rejestru R20
	add R16, R20			; dodaj zawarto�� rejestru R20 do rejestru R16, wynik zapisz w R16
	brcs carrySet0			; skocz je�li nast�pi�o przeniesienie z MSB m�odszej cz�ci i dodaj 1
							; do cz�ci starszej
	rjmp continue0			; pomi� dodawanie 1
carrySet0:					; dodaj jeden do starszej cz�ci
	ldi R20, 1				; za�aduj warto�� 1 do rejestru R20
	add R17, R20			; dodaj zawarto�� rejestru R20 do rejestru R17, wynik zapisz w R17

							; ---
							; uzyskaj warto�� arytmetycznie przeciwn� do uzyskanej z dodania 100ms
							; do warto�ci po�redniej licznika
							; przyk�adowo dla warto�ci (1954 + 97 = 2051) uzyskaj (-2051)
							; wynik zapisz w R17_R16
							; ---
continue0:					; kontynuacja programu
	mov R21, R16			; kopiuj zawarto��rejestru R16 do rejestru R21
	mov R22, R17			; kopiuj zawarto��rejestru R17 do rejestru R22
	com R16					; neguj bity rejestru R16
	com R17					; neguj bity rejestru R16
							; dodaj 1 w celu konwersji w zapis U2 (liczba jest ujemna)
	ldi R20, 1				; za�aduj warto�� 1 do rejestru R20
	add R16, R20			; dodaj zawarto�� rejestru R20 do rejestru R16, wynik zapisz w R16
	brcs carrySet1			; skocz je�li nast�pi�o przeniesienie z MSB m�odszej cz�ci i dodaj 1
							; do cz�ci starszej
	rjmp continue1			; pomi� dodawanie 1
carrySet1:					; dodaj jeden do starszej cz�ci
	ldi R20, 1				; za�aduj warto�� 1 do rejestru R20
	add R17, R20			; dodaj zawarto�� rejestru R20 do rejestru R17, wynik zapisz w R17

							; ---
							; wczytaj warto�� maksymaln� licznika timera do R19_R18, czyli 3 sekundy
							; do tej warto�ci dodaj uprzednio uzyskan� warto�� przeciwn�
							; przyk�adowo dla pierwszego przerwania b�dzie to -2,1 sekundy
							; otrzymamy wtedy zapas czasu jaki zosta� nam do 3 sekund, czyli
							; przy pierwszym przerwaniu b�dzie to 900ms
							; wynik zapisz w R17_R16
							; ---
continue1:					; kontynuacja programu
	in R18, ICR1L			; wczytaj m�odsz� cz�� rejestru ICR1 do rejestru R18
	in R19, ICR1H			; wczytaj starsz� cz�� rejestru ICR1 do rejestru R19
	add R16, R18			; dodaj zawarto�� rejestru R18 do rejestru R16, wynik zapisz w R16
	brcs carrySet2			; skocz je�li nast�pi�o przeniesienie z MSB m�odszej cz�ci i dodaj 1
							; do cz�ci starszej
	rjmp continue2			; pomi� dodawanie 1
carrySet2:					; dodaj jeden do starszej cz�ci
	ldi R20, 1				; za�aduj warto�� 1 do rejestru R20
	add R17, R20			; dodaj zawarto�� rejestru R20 do rejestru R17, wynik zapisz w R17
continue2:					; kontynuacja programu
	add R17, R19			; dodaj zawarto�� rejestru R19 do rejestru R17, wynik zapisz w R17

	brne fine				; skocz je�li starsza cz�ci R17_R16 jest r�na od zera
							; wtedy zapas 100ms zawsze jest dost�pny, gdy� warto��
							; starszej cz�ci zaczyna si� od 256 co jest wi�ksze od 97

							; je�li w starszej cz�ci R17_R16 mamy 0, to por�wnaj m�odsze cz�ci
							; odejmij 100ms od m�odszej cz�ci R17_R16
							; je�eli wynik b�dzie nieujemny, to mo�emy zaktualizowa�
							; warto�� po�redni� licznika timera w OCR1A, warto�ci� zapisan�
							; w R22_R21
	ldi R20, -97			; za�aduj warto�� -97 do rejestru R20
	add R16, R20			; odejmij 97 od m�odszej cz�ci R17_R16
	brmi end				; je�li wynik jest ujemny, to skocz na koniec podrpogramu
							; obs�ugi przerwania i nie aktualizuj OCR1A

fine:						; zaktualizuj warto�� OCR1A
	in R16, TCCR1B			; wy��cz timer (od��czenie �r�d�a taktowania)
	andi R16, 0b11111000
	out TCCR1B, R16

	in R16, TCCR1A			; zresetowanie trybu pracy timera (docelowy tryb Normal)
	andi R16, 0b11111100
	out TCCR1A, R16
	in R16, TCCR1B
	andi R16, 0b11100111
	out TCCR1B, R16

	out OCR1AH, R22			; aktualizacja warto�ci po�redniej licznika timera
	out OCR1AL, R21

	in R16, TCCR1A			; przywr�cenie trybu timera 'Fast PWM'
	ori R16, 0b00000010
	andi R16, 0b11111110
	out TCCR1A, R16
	in R16, TCCR1B
	ori R16, 0b00011000
	out TCCR1B, R16

	in R16, TCCR1B			; w��cz timer (pod��czenie �r�d�a taktowania z preskalerem 1/1024)
	andi R16, 0b11111101
	ori R16, 0b00000101
	out TCCR1B, R16
end:						; zako�czenie podprogramu obs�ugi przerwania
	pop R16					; zdejmij ze stosu pierwotn� warto�� SREG i zapisz w R16
	out SREG, R16			; przywr�� zachowany rejestr SREG
	pop R16					; przywr�� zachowany rejestr R16
	pop R17					; przywr�� zachowany rejestr R17
	pop R18					; przywr�� zachowany rejestr R18
	pop R19					; przywr�� zachowany rejestr R19
	pop R20					; przywr�� zachowany rejestr R20
	pop R21					; przywr�� zachowany rejestr R21
	pop R22					; przywr�� zachowany rejestr R22
	reti					; powr�� z podprogramu obs�ugi przerwania INT0
							; jednocze�nie ustawiaj�c flag� zezwolenia na przerwania w SREG

main:						; program g��wny
	call EXT_INT0
    rjmp main				; wr�� na pocz�tek programu g��wnego