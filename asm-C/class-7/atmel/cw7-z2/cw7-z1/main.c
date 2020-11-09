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
		control = (PINB | 0b11110000) ^ (0b00010000 << col);
		PORTB = control;
		asm volatile ("nop");
		control = PINB;
		if ((control & 0b00001111) != 0b00001111) {
			row = 0;
			while (row < 4) {
				if ((control & (0b00000001 << row)) != (0b00000001 << row)) {
					if (!isKeyLocked(col, row)) {
						lockKey(col, row);
						uint8_t out = 0b10000000;
						out |= col << 2; // ew zamienic z row
						out |= row;
						PORTA = out;
						_delay_ms(50);
					}
				} else {
					unlockKey(col, row);
				}
				row++;
			}
		} else {
			clearKeyLocks();
			PORTA = 0b00000000;
		}
		col++;
	}
}

void keypadScan() {
	PORTB |= 0b11110000;
	asm volatile ("nop");
	PORTB &= 0b00001111;
	asm volatile ("nop");
	if ((PINB & 0b00001111) == 0b00001111) {
		clearKeyLocks();
		PORTA = 0b00000000;
		return;
	}
	PORTB |= 0b11110000;
	
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
    DDRB = 0b11110000;
	PORTB = 0b11110000;
	PORTB |= 0b00001111;
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	Timer0Init();
	sei();
	
    while (1) {
		if (!timerStarted) {
			keypadScan();
		}
    }
}
