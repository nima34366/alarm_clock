/*
 * menu_display.c
 *
 * Created: 4/26/2021 12:30:55 PM
 * Author : wickr
 */ 

#ifndef F_CPU			
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h" //includes all commands to Control LCD

int state=0; //To check whether a button is already pressed or not 
int C=0; //number displayed in the LCD
char C_string[10];

int main(void)
{
	LCD_Init(); //Initializing the LCD
	LCD_String("0");
	PORTC=0b0111; //Enabling pull-up in PC0,PC1,PC2 pins
	while (1)
	{
		
		_delay_ms(50); //To deal with button bounce;
		
		if((state==0) && (PINC==70)) //Increase if button1 pressed
		{ 
			C=C+1;
			LCD_Clear();
			sprintf(C_string,"%d",C);
			LCD_String(C_string);

		}
		
		else if((state==0) && (PINC==69)) //Decrease if button2 pressed
		{
			LCD_String("b");
			C=C-1;
			LCD_Clear();
			sprintf(C_string,"%d",C);
			LCD_String(C_string);
		}
		
		else if((state==0) && (PINC==67)) //Reset if button3 pressed
		{
			C=0;
			LCD_Clear();
			sprintf(C_string,"%d",C);
			LCD_String(C_string);
		}
		
		if((PINC==70)||(PINC==69)||(PINC==67)) //checking whether button is pressed or not
		{
			state=1;
		}
		else
		{
			state=0;
		}
		
	}
}