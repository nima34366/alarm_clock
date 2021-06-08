
#ifndef KEYPAD_H_
#define KEYPAD_H_
	
#include <avr/io.h>
#include <util/delay.h>

#define  data_diection_d DDRD
#define  port_state_d PORTD

inline int Keypad_read()
{
	data_diection_d = 0b11111111;    //DDRC 1 output, 0 input	
	while (1)
	{	port_state_d = 0b00001111;   //PORTC 1 high, 0 low
		int colomn = PIND & 0b11110000; // check which colomn pressed
		
		port_state_d = 0b11110000;
		int row = PIND & 0b00001111; // check which colomn pressed
		//row1 set to PC0 and so on, colom1 set to PC4 and so on//
		
		if ((colomn == 1<<4) & (row == 1)){return 1; } 
		if ((colomn == 1<<5) & (row == 1)){return 2; }
		if ((colomn == 1<<6) & (row == 1)){return 3; }
		if ((colomn == 1<<4) & (row == 1<<3)){return  10;}
		
		if ((colomn == 1<<4) & (row == 1<<1)){return  4; }
		if ((colomn == 1<<5) & (row == 1<<1)){return  5; }
		if ((colomn == 1<<6) & (row == 1<<1)){return  6; }
		if ((colomn == 1<<6) & (row == 1<<3)){return  20;}
		
		if ((colomn == 1<<4) & (row == 1<<2)){return  7; }
		if ((colomn == 1<<5) & (row == 1<<2)){return  8; }
		if ((colomn == 1<<6) & (row == 1<<2)){return  9; }
		if ((colomn == 1<<5) & (row == 1<<3)){return  0; }
		_delay_ms(100);
	}
}

inline int menu_read(){
	data_diection_d |= 1<<7;
	if (PIND==1<<7){return 1;} 
	else {return 0;}	
}

#endif /* KEYPAD_H_ */