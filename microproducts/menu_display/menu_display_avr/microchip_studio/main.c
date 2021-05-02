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
#include <stdio.h>

int P=0;
int C=0;
char result[10];



int main(void)
{
	lcd_init(LCD_DISP_ON); /*initialize lcd,display on, cursor on */
	lcd_puts("0");
	PORTB=0b0111;
    while (1) 
    {
		_delay_ms(50);
		if((P==0) && (PINB==0b0110)){
			C=C+1;
			lcd_clrscr();
			sprintf(result,"%d",C);
			lcd_puts(result);
		}
		else if((P==0) && (PINB==0b0101))
		{
			C=C-1;
			lcd_clrscr();
			sprintf(result,"%d",C);
			lcd_puts(result);
		}
		else if((P==0) && (PINB==0b0011))
		{
			C=0;
			lcd_clrscr();
			sprintf(result,"%d",C);
			lcd_puts(result);
		}
		if((PINB==0b0110)||(PINB==(0b0101))||(PINB==(0b0011)))
		{
			P=1;
		}
		else
		{
			P=0;
		}
		
		
    }
}

