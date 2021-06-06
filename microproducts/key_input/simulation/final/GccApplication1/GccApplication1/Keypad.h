
#ifndef KEYPAD_H_
#define KEYPAD_H_
	
#include <avr/io.h>
#include <util/delay.h>

#define  data_diection_c DDRC
#define  port_state_c PORTC

int Keypad_read()
{
	data_diection_c = 0b11110000;    //DDRC 1 output, 0 input
	port_state_c = 0b00001111;   //PORTC 1 high, 0 low
	int row = PINC & 0b11110000 ; // check which row pressed

	data_diection_c = 0b00001111;    
	port_state_c = 0b11110000;   
	int colomn = PINC & 0b00001111 ; // check which row pressed
	int press;
	
	//row1 set to PC0 and so on, colom1 set to PC4 and so on//
	
	while (1)
	{
		if ((row == 0b00010000) & (colomn == 0b00000001)){press = 1; } 
		if ((row == 0b00100000) & (colomn == 0b00000001)){press = 2; }
		if ((row == 0b01000000) & (colomn == 0b00000001)){press = 3; }
		if ((row == 0b10000000) & (colomn == 0b00000001)){press = 10;}
		
		if ((row == 0b00010000) & (colomn == 0b00000010)){press = 4; }
		if ((row == 0b00100000) & (colomn == 0b00000010)){press = 5; }
		if ((row == 0b01000000) & (colomn == 0b00000010)){press = 6; }
		if ((row == 0b10000000) & (colomn == 0b00000010)){press = 20;}
		
		if ((row == 0b00010000) & (colomn == 0b00000100)){press = 7; }
		if ((row == 0b00100000) & (colomn == 0b00000100)){press = 8; }
		if ((row == 0b01000000) & (colomn == 0b00000100)){press = 9; }
		if ((row == 0b10000000) & (colomn == 0b00000100)){press = 30;}

		if ((row == 0b10000000) & (colomn == 0b00001000)){press = 40;}
		else {return 0;}
		_delay_ms(100);
		return press;
	}
}

#endif /* KEYPAD_H_ */