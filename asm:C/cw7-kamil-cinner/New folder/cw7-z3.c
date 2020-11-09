/*
 * cw7-z3.c
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

volatile uint8_t numbersCount = 0;

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
	PORTD &= 0b00001111;
	if (col > 3) {
		col = 0;
	}

	uint8_t control;

	control = (PIND & 0b00001111) | (0b00010000 << col);
	PORTD = control;
	asm volatile ("nop");
	control = PIND;
	row = 0;
	while (row < 4) {
		if ((control & (0b00000001 << row)) == (0b00000001 << row)) {
			if (!isKeyLocked(col, row)) {
				if (numbersCount < 4) {
					lockKey(col, row);
					uint8_t keyCode = 0b00000000;
					keyCode |= col << 2;
					keyCode |= row;
					uint8_t out;
					uint8_t mask = 0b11110000;
					if (numbersCount < 2) {
						mask >>= (numbersCount * 4);
						out = PINA;
						out |= (keyCode << (numbersCount * 4));
						out &= ((keyCode << (numbersCount * 4)) | mask);
						PORTA = out;
					} else {
						mask >>= ((numbersCount - 2) * 4);
						out = PINB;
						out |= (keyCode << ((numbersCount - 2) * 4));
						out &= ((keyCode << ((numbersCount - 2) * 4)) | mask);
						PORTB = out;
					}
					numbersCount++;
				}
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
    DDRD |= 0b11110000;
	DDRD &= 0b11110000;

	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	DDRB = 0b11111111;
	PORTB = 0b00000000;
	
	Timer0Init();
	sei();
	
    while (1) {}
}
