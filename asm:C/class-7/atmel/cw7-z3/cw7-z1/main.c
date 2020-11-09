/*
 * cw7-z1.c
 *
 * Created: 10/24/2020 11:47:54 AM
 * Author : Kamil Cinner
 */ 
#define F_CPU 1000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

volatile bool timerStarted = false;

volatile bool keyLocks[] = {
	false, false, false, false,
	false, false, false, false,
	false, false, false, false,
	false, false, false, false
};

volatile uint8_t numbersCount = 0;

void clearKeyLocks() {
	uint8_t i = 0;
	while (i < 16) {
		keyLocks[i] = false;
		i++;
	}
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
	// Stop timer
	TCCR0 &= 0b11111000;
	timerStarted = false;
	
	uint8_t col = 0;
	uint8_t row;
	uint8_t control;
	while (col < 4) {
		control = (PIND | 0b11110000) ^ (0b00010000 << col);
		PORTD = control;
		asm volatile ("nop");
		control = PIND;
		row = 0;
		while (row < 4) {
			if ((control & (0b00000001 << row)) != (0b00000001 << row)) {
				if (!isKeyLocked(col, row)) {
					lockKey(col, row);
					uint8_t keyCode = 0b00000000;
					keyCode |= col << 2; // ew zamienic z row
					keyCode |= row;
					uint8_t out;
					uint8_t mask = 0b11110000;
					//if (numbersCount != 0b0000000) mask = 0b00001111;
					//if (numbersCount != 0b00000010) mask = 0b00001111;
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
					_delay_ms(50);
				}
			} else {
				unlockKey(col, row);
			}
			row++;
		}
		col++;
	}
}

void keypadScan() {
	PORTD |= 0b11110000;
	asm volatile ("nop");
	PORTD &= 0b00001111;
	asm volatile ("nop");
	if ((PIND & 0b00001111) == 0b00001111) {
		clearKeyLocks();
		return;
	}
	PORTD |= 0b11110000;
	
	// Start timer
	TCCR0 = (TCCR0 & 0b11111100) | 0b00000100;
	timerStarted = true;
}

void Timer0Init() {
	OCR0 = 20;
	TCCR0 = (TCCR0 & 0b10111111) | 0b00001000;
	TIMSK |= 0b00000010;
}

int main(void) {
    DDRD = 0b11110000;
	PORTD = 0b11110000;
	PORTD |= 0b00001111;
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	
	Timer0Init();
	sei();
	
    while (numbersCount < 4) {
		if (!timerStarted) {
			keypadScan();
		}
    }
}
