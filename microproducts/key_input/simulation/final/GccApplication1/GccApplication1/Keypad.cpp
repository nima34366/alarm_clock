#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
 
int Keypad_read()
{
	DDRC = 0b11110000;    /* pc4,pc5,pc6,pc7 set as output */
	PORTC = 0b00001111;   /* pc0-pc2 outputs turn on (HIGH)*/
	int key1 = PINC & 0b11110000 ;

	DDRC = 0b00001111;    /* pc0,pc1,pc2,pc3 set as output */
	PORTC = 0b11110000;   /* pc4-pc7 outputs turn on (HIGH)*/
	int key2 = PINC & 0b00001111 ;
	int press;
	
	while (1)
	{	
		if ((key1 == 0b00010000) & (key2 == 0b00000001)){press = 1; }
		if ((key1 == 0b00100000) & (key2 == 0b00000001)){press = 2; }
		if ((key1 == 0b01000000) & (key2 == 0b00000001)){press = 3; }
		if ((key1 == 0b10000000) & (key2 == 0b00000001)){press = 10;}
		
		if ((key1 == 0b00010000) & (key2 == 0b00000010)){press = 4; }
		if ((key1 == 0b00100000) & (key2 == 0b00000010)){press = 5; }
		if ((key1 == 0b01000000) & (key2 == 0b00000010)){press = 6; }
		if ((key1 == 0b10000000) & (key2 == 0b00000010)){press = 20;}
		
		if ((key1 == 0b00010000) & (key2 == 0b00000100)){press = 7; }
		if ((key1 == 0b00100000) & (key2 == 0b00000100)){press = 8; }
		if ((key1 == 0b01000000) & (key2 == 0b00000100)){press = 9; }
		if ((key1 == 0b10000000) & (key2 == 0b00000100)){press = 30;}

		if ((key1 == 0b10000000) & (key2 == 0b00001000)){press = 40;}
		else {return 0;}
		_delay_ms(100);
	return press;
		}
}
