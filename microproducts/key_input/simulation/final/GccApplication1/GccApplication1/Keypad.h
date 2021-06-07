
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
	int colomn = PINC & 0b11110000 ; // check which colomn pressed

	data_diection_c = 0b00001111;    
	port_state_c = 0b11110000;   
	int row = PINC & 0b00001111 ; // check which colomn pressed
	int press;
	
	//row1 set to PC0 and so on, colom1 set to PC4 and so on//
	
	while (1)
	{
		if ((colomn == 1<<4) & (row == 1)){press = 1; } 
		if ((colomn == 1<<5) & (row == 1)){press = 2; }
		if ((colomn == 1<<6) & (row == 1)){press = 3; }
		if ((colomn == 1<<4) & (row == 1<<3)){press = 10;}
		
		if ((colomn == 1<<4) & (row == 1<<1)){press = 4; }
		if ((colomn == 1<<5) & (row == 1<<1)){press = 5; }
		if ((colomn == 1<<6) & (row == 1<<1)){press = 6; }
		if ((colomn == 1<<6) & (row == 1<<3)){press = 20;}
		
		if ((colomn == 1<<4) & (row == 1<<2)){press = 7; }
		if ((colomn == 1<<5) & (row == 1<<2)){press = 8; }
		if ((colomn == 1<<6) & (row == 1<<2)){press = 9; }
		
		else {return 0;}
		_delay_ms(100);
		return press;
	}
}
int menu_read(){
	data_diection_c |= 1<<7;
	if (PINC==1<<7){return 1;} 
	else {return 0;}
	
}

#endif /* KEYPAD_H_ */