; Autor: Kamil Cinner
;
sbi DDRA, 0			; ustaw PA.0 jako liniê wyjœciow¹		

main:				; program g³ówny
	sbis PINA, 1	; jeœli PA.1=1, to pomiñ nastêpn¹ instrukcjê
	cbi PORTA, 0	; ustaw PA.0=0
	sbic PINA, 1	; jeœli PA.1=0, to pomiñ nastêpn¹ instrukcjê
	sbi PORTA, 0	; ustaw PA.0=1
	rjmp main		; wróæ na pocz¹tek programu g³ównego
	