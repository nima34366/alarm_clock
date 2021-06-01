#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"


int main(void)
{	DDRB = 0b11111111; /* for light pins set to output */
	DDRD = 0b10000000;
	
	while (1)
	{	int key1, key2;
		
		keypd(&key1, &key2);
		
		if ((key1 == 0b00001000) & (key2 == 0b00000100)){PORTB = 0b10000000; }
		if ((key1 == 0b00010000) & (key2 == 0b00000100)){PORTB = 0b11000000; }
		if ((key1 == 0b00100000) & (key2 == 0b00000100)){PORTB = 0b11100000; }
		
		if ((key1 == 0b00001000) & (key2 == 0b00000010)){PORTB = 0b11110000; }
		if ((key1 == 0b00010000) & (key2 == 0b00000010)){PORTB = 0b11111000; }
		if ((key1 == 0b00100000) & (key2 == 0b00000010)){PORTB = 0b11111100; }
		
		if ((key1 == 0b00001000) & (key2 == 0b00000001)){PORTB = 0b11111110; }
		if ((key1 == 0b00010000) & (key2 == 0b00000001)){PORTB = 0b11111111; }
		if ((key1 == 0b00100000) & (key2 == 0b00000001)){PORTB = 0b11111111; PORTD = 0b10000000; }
		_delay_ms(100);
		PORTB = 0x0;
		PORTD = 0;
	}
	return 0;
}