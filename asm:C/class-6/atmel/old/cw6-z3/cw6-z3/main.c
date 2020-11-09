/*
 * cw6-z3.c
 *
 * Created: 10/24/2020 11:47:54 AM
 * Author : Kamil Cinner
 */ 

#define LeftButton 0
#define RightButton 3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

bool keyCaptured = false;
bool timerStarted = false;

void keypadScan() {
	// If keypad is not pressed don't do anything
	if ((PINA & 0b00000001) == 0b00000001) {
		keyCaptured = false;
		PORTB = 0b00000000;
		return;
	}
	
	// Start timer
	TCCR0 = (TCCR0 & 0b11111101) | 0b00000101;
	timerStarted = true;
}

int main(void) {
    DDRA = (DDRA | 0b11110000) & 0b11111110;
	PORTA |= 0b11110001;
	DDRB = 0b11111111;
	
	sei();
	
	OCR0 = 5;
	TCCR0 = (TCCR0 & 0b10111111) | 0b00001000;
	TIMSK |= 0b00000010;
	
    while (1) {
		if (!keyCaptured && !timerStarted) {
			keypadScan();
		}
		if (keyCaptured && (PINA & 0b00000001) == 0b00000001) {
			keyCaptured = false;
		}
    }
}

ISR(TIMER0_COMP_vect) {
	cli();
	
	uint8_t col = 0;
	uint8_t control;
	while (col < 4) {
		control = (PORTA | 0b11110000) ^ (0b00010000 << col);
		PORTA = control;
		asm volatile ("nop");
		control = PINA;
		if ((control & 0b00000001) != 0b00000001) {
			PORTB = 0b10000000 | col;
		}
		col++;
	}
	keyCaptured = true;
	PORTA |= 0b11110000;
	
	// Stop timer
	TCCR0 &= 0b11111000;
	timerStarted = false;
	
	reti();
}
