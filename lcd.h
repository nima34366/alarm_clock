/*
 * lcd.h
 *
 * Created: 6/4/2021 4:53:07 PM
 *  Author: Nima Wickramasinghe
 */ 


#ifndef LCD_H_
#define LCD_H_


#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>
#include <string.h>




#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */


void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}


void LCD_String (const char* str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_Int (int n)		/* Send Int to LCD function */
{
	char str[1];
	sprintf(str,"%d",n);
	LCD_String(str);
}

void LCD_String_xy (char row, char pos,const char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_Main(const char *Time,const char *Date)
{
	LCD_Clear();
	LCD_String_xy(0,4,Time);
	LCD_String_xy(1,3,Date);
}

void LCD_Menu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1.TIME");
	LCD_String_xy(0,8,"2.ALARM");
	LCD_String_xy(1,0,"3.RESET");
	LCD_String_xy(1,8,"4.BACK");
}

void LCD_Invalidinput()
{
	LCD_Clear();
	LCD_String_xy(0,2,"INVALID INPUT");
}

void LCD_SetTimeMenu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1.SET TIME");
	LCD_String_xy(0,8,"2.SET DATE");
	LCD_String_xy(1,0,"3.BACK");
}

void LCD_AlarmMenu(char *alarms[4])
{
	LCD_Clear();
	char alarm0[10] = "1.";
	char alarm1[10] = "2.";
	char alarm2[10] = "3.";
	char alarm3[10] = "4."; 
	strcat(alarm0,alarms[0]);
	strcat(alarm1,alarms[1]);
	strcat(alarm2,alarms[2]);
	strcat(alarm3,alarms[3]);
	LCD_String_xy(0,0,alarm0);
	LCD_String_xy(0,8,alarm1);
	LCD_String_xy(1,0,alarm2);
	LCD_String_xy(1,8,alarm3);
}

void LCD_AlarmOptions()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1.CHANGE");
	LCD_String_xy(0,8,"2.DELETE");
	LCD_String_xy(1,0,"3.TONE");
	LCD_String_xy(1,8,"4.BACK");
}

#endif /* LCD_H_ */