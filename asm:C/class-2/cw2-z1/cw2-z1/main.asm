; Autor: Kamil Cinner
;
sbi DDRA, 0			; ustaw PA.0 jako lini� wyj�ciow�		

main:				; program g��wny
	sbis PINA, 1	; je�li PA.1=1, to pomi� nast�pn� instrukcj�
	cbi PORTA, 0	; ustaw PA.0=0
	sbic PINA, 1	; je�li PA.1=0, to pomi� nast�pn� instrukcj�
	sbi PORTA, 0	; ustaw PA.0=1
	rjmp main		; wr�� na pocz�tek programu g��wnego
	