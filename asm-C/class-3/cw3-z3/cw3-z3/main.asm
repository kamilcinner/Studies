;
; cw3-z3.asm
;
; Created: 10/12/2020 7:30:55 PM
; Author : Kamil Cinner
;
ser R16						; ustaw wszystkie bity w rejestrze R16
out DDRA, R16				; ustaw jako linie wyjœciowe wszystkie piny PA

main:						; program g³ówny
	ldi R16, 0b11110000		; za³aduj sta³¹ 11110000 (bin) do rejestru R16
	in R17, PINB			; wczytaj zawartoœæ rejestru PINB do rejestru R17
	mov R18, R17			; kopiuj zawartoœæ rejestru R17 do rejestru R18
	ori R17, 0b00000001		; wykonaj sumê logiczn¹ zawartoœci rejestru R17 i wartoœci 00000001 (bin), wynik zapisz do R17, po tej operacji R17.0=1
	cpse R17, R18			; porównaj rejestry R17 i R18, a jeœli s¹ równe, to pomiñ kolejn¹ instrukcjê (pomiñ jeœli PB.0=1)
	com R16					; neguj bity rejestru R16
	out PORTA, R16			; zapisz zawartoœæ rejestru R16 do rejestru PORTA
	rjmp main				; skocz na pocz¹tek programu g³ównego
