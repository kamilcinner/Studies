/*
 * cw7-z2.c
 *
 * Author : Kamil Cinner
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool keyLocks[] = {
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false, false, false
};

volatile uint8_t col = 0;
volatile uint8_t row;

bool checkKeyLocksCleared() {
	uint8_t i = 0;
	while (i < 16) {
		if (keyLocks[i]) {
			return false;
		}
		i++;
	}
	return true;
}

void lockKey(uint8_t col, uint8_t row) {
	keyLocks[(4 * col) + row] = true;
}

void unlockKey(uint8_t col, uint8_t row) {
	keyLocks[(4 * col) + row] = false;
}

bool isKeyLocked(uint8_t col, uint8_t row) {
	return keyLocks[(4 * col) + row];
}

ISR(TIMER0_COMP_vect) {
	PORTB &= 0b00001111;
	if (col > 3) {
		if (checkKeyLocksCleared()) {
			PORTA = 0b00000000;
		}
		col = 0;
	}

	uint8_t control;

	control = (PINB & 0b00001111) | (0b00010000 << col);
	PORTB = control;
	asm volatile ("nop");
	control = PINB;
	row = 0;
	while (row < 4) {
		if ((control & (0b00000001 << row)) == (0b00000001 << row)) {
			if (!isKeyLocked(col, row)) {
				lockKey(col, row);
				uint8_t keyCode = 0b10000000;
				keyCode |= col << 2;
				keyCode |= row;
				PORTA = keyCode;
			}
		} else {
			unlockKey(col, row);
		}
		row++;
	}
	col++;
}

void Timer0Init() {
	OCR0 = 1;
	TCCR0 = (TCCR0 & 0b10111111) | 0b00001000;
	TIMSK |= 0b00000010;
	TCCR0 = (TCCR0 & 0b11111101) | 0b00000101;
}

int main(void) {
    DDRB |= 0b11110000;
	DDRB &= 0b11110000;

	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	Timer0Init();
	sei();
	
    while (1) {}
}
