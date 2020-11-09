;
; cw3-z3.asm
;
; Created: 10/12/2020 7:30:55 PM
; Author : Kamil Cinner
;
ser R16						; ustaw wszystkie bity w rejestrze R16
out DDRA, R16				; ustaw jako linie wyj�ciowe wszystkie piny PA

main:						; program g��wny
	ldi R16, 0b11110000		; za�aduj sta�� 11110000 (bin) do rejestru R16
	in R17, PINB			; wczytaj zawarto�� rejestru PINB do rejestru R17
	mov R18, R17			; kopiuj zawarto�� rejestru R17 do rejestru R18
	ori R17, 0b00000001		; wykonaj sum� logiczn� zawarto�ci rejestru R17 i warto�ci 00000001 (bin), wynik zapisz do R17, po tej operacji R17.0=1
	cpse R17, R18			; por�wnaj rejestry R17 i R18, a je�li s� r�wne, to pomi� kolejn� instrukcj� (pomi� je�li PB.0=1)
	com R16					; neguj bity rejestru R16
	out PORTA, R16			; zapisz zawarto�� rejestru R16 do rejestru PORTA
	rjmp main				; skocz na pocz�tek programu g��wnego
