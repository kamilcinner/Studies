/*
 * cw6-z2.c
 *
 * Created: 10/24/2020 11:47:54 AM
 * Author : Kamil Cinner
 */ 

#define LeftButton 0
#define RightButton 3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool timerStarted = false;

volatile bool keyLocks[] = {
	false, false, false, false
};

volatile uint8_t keyPressedCount = 0;

void clearKeyLocks() {
	uint8_t i = 0;
	while (i < 4) {
		keyLocks[i] = false;
		i++;
	}
}

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
	// Stop timer
	TCCR0 &= 0b11111000;
	timerStarted = false;
	
	uint8_t col = 0;
	uint8_t control;
	while (col < 4) {
		control = (PINB | 0b11110000) ^ (0b00010000 << col);
		PORTB = control;
		asm volatile ("nop");
		control = PINB;
		if ((control & 0b00000001) != 0b00000001) {
			if (!isKeyLocked(col)) {
				lockKey(col);
				PORTA = (control >> 4);
			}
		} else {
			unlockKey(col);
		}
		col++;
	}
}

void keypadScan() {
	//PORTB |= 0b11110001;
	PORTB = 0xff;
	asm volatile ("nop");
	PORTB &= 0b00001111;
	asm volatile ("nop");
	if ((PINB & 0b00000001) == 0b00000001) {
		clearKeyLocks();
		PORTA = 0b00000000;
		return;
	}
	
	// Start timer
	TCCR0 = (TCCR0 & 0b11111101) | 0b00000101;
	timerStarted = true;
}

void Timer0Init() {
	OCR0 = 1;
	TCCR0 = (TCCR0 & 0b10111111) | 0b00001000;
	TIMSK |= 0b00000010;
}

int main(void) {
    //DDRB |= 0b11110000;
	//DDRB &= 0b11111110;
	DDRB = 0xf0;
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
