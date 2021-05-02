/*
 * menu_display.c
 *
 * Created: 4/26/2021 12:30:55 PM
 * Author : wickr
 */ 

#ifndef F_CPU			
#define F_CPU 1000000UL			  
#endif

#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>

int main(void)
{
	lcd_init(LCD_DISP_ON); /*initialize lcd,display on, cursor on */
    while (1) 
    {
		PORTB=0b0111;
		_delay_ms(50);
		if((PINB==0b0110)||(PINB==(0b0101))||(PINB==(0b0011)))
		{
			lcd_clrscr();
			lcd_puts("ON");
		}
		else
		{
			lcd_clrscr();
			lcd_puts("OFF");
		}
		
		
    }
}

