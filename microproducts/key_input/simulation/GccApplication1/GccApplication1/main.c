#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
int  key1, key2;
void keypd();

int main(void)
{	DDRB = 0b11111111; /* for light pins set to output */
	DDRD = 0b10000000;
	
	while (1)
	{
		keypd();
	}
	return 0;
}

void keypd()
{
	DDRC = 0b00000111;    /* pc0,pc1,pc2 set as output */	
	PORTC = 0b00111000;   /* pc0-pc2 outputs turn on (HIGH)*/
	key2 = PINC & 0b00000111 ;
	
	DDRC = 0b00111000;    /* pc3,pc4,pc5 set as output */
	PORTC = 0b00000111;   /* pc0-pc2 outputs turn on (HIGH)*/
	key1 = PINC & 0b00111000 ;
	
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