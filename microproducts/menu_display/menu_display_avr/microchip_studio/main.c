/*
 * menu_display.c
 *
 * Created: 4/26/2021 12:30:55 PM
 * Author : wickr
 */ 

#include <avr/io.h>
#include "lcd.h"

int main(void)
{
	lcd_init(LCD_DISP_ON_CURSOR); /*initialize lcd,display on, cursor on */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */
	lcd_puts("Line1");        /* type something random */
	lcd_gotoxy(0,1);          /* go to 2nd row 1st col */
	lcd_puts("Line2");  /* type something random */
    /* Replace with your application code */
    while (1) 
    {
    }
}

