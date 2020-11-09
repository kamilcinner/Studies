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

ISR(INT0_vect) {
	uint8_t col = 0;
	uint8_t control;
	while (col < 4) {
		control = (PIND & 0b00001111) | (0b00010000 << col);
		PORTD = control;
		asm volatile ("nop");
		control = PIND;
		if ((control & 0b00000100) == 0b00000100) {
			if (!isKeyLocked(col)) {
				lockKey(col);
				PORTA = col + 1;
			}
		} else {
			unlockKey(col);
			col++;
		}
	}
}

int main(void) {
    DDRD |= 0b11110000;
	DDRD &= 0b11111110;
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	
	GICR |= 0b01000000;
	
	sei();
	
    while (1) {}
}
