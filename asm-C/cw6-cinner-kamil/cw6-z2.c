/*
 * cw6-z2.c
 *
 * Author : Kamil Cinner
 */ 

#define LeftButton 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool keyLocks[] = {
	false, false, false, false
};

volatile uint8_t col = 0;

volatile uint8_t keyPressCount = 0;

void lockKey(uint8_t index) {
	keyLocks[index] = true;
}

void unlockKey(uint8_t index) {
	keyLocks[index] = false;
}

bool isKeyLocked(uint8_t index) {
	return keyLocks[index];
}

ISR(TIMER0_COMP_vect) {
	cli();
	if (col > 3) {
		col = 0;
	}

	uint8_t control;

	control = (PIND & 0b00001111) | (0b00010000 << col);
	PORTD = control;
	asm volatile ("nop");
	control = PIND;
	if ((control & 0b00000001) == 0b00000001) {
		if (!isKeyLocked(col)) {
			lockKey(col);
			if (col == LeftButton) {
				keyPressCount++;
				PORTA = keyPressCount;
			}
		}
	} else {
		unlockKey(col);
	}

	col++;
}

void Timer0Init() {
	OCR0 = 10;
	TCCR0 = (TCCR0 & 0b10111111) | 0b00001000;
	TIMSK |= 0b00000010;
	TCCR0 = (TCCR0 & 0b11111101) | 0b00000101;
}

int main(void) {
    DDRD |= 0b11110000;
	DDRD &= 0b11111110;
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	Timer0Init();
	sei();
	
    while (1) {}
}
