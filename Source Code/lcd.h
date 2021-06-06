/*
 * lcd.h
 *
 * Created: 6/4/2021 4:53:07 PM
 *  Author: Nima Wickramasinghe
 */ 


#ifndef LCD_H_
#define LCD_H_


////////////////////////////////////////////////////////
//CONTAINS ALL LCD CONTROLS. SKIP TO CENTRAL FUNCTIONS//
////////////////////////////////////////////////////////

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

/////////////////////
//CENTRAL FUNCTIONS//
/////////////////////

void LCD_Home(const char *Time,const char *Date)
{
	LCD_Clear();
	LCD_String_xy(0,6,Time);
	LCD_String_xy(1,4,Date);
}

void LCD_Menu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>D&T");
	LCD_String_xy(0,8,"2>ALARM");
	LCD_String_xy(1,0,"3>RESET");
	LCD_String_xy(1,8,"4>BACK");
}

void LCD_Invalidinput()
{
	LCD_Clear();
	LCD_String_xy(0,1,"INVALID INPUT");
}

void LCD_SetTimeMenu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>TIME");
	LCD_String_xy(0,8,"2>DATE");
	LCD_String_xy(1,0,"3>BACK");
}

void LCD_AlarmList(const char *alarms[4]) // Insert in array of "00:00"
{
	LCD_Clear();
	char alarm0[10]= "1>";
	char alarm1[10]= "2>";
	char alarm2[10]= "3>";
	char alarm3[10]= "4>"; 
	strcat(alarm0,alarms[0]);
	strcat(alarm1,alarms[1]);
	strcat(alarm2,alarms[2]);
	strcat(alarm3,alarms[3]);
	LCD_String_xy(0,0,alarm0);
	LCD_String_xy(0,8,alarm1);
	LCD_String_xy(1,0,alarm2);
	LCD_String_xy(1,8,alarm3);
}

void LCD_AlarmMenu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>SET");
	LCD_String_xy(0,8,"2>DELETE");
	LCD_String_xy(1,0,"3>TONE");
	LCD_String_xy(1,8,"4>BACK");
}

void LCD_Tone()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>STARW");
	LCD_String_xy(0,8,"2>HARRYP");
	LCD_String_xy(1,0,"3>GOT");
	LCD_String_xy(1,8,"4>GREENL");
}

void LCD_Ringing()
{
	LCD_Clear();
	LCD_String_xy(0,6,"WAKE");
	LCD_String_xy(1,7,"UP");
}

////////////////
//SETTING TIME//
////////////////

void LCD_SetTime_H1()
{
	LCD_Clear();
	LCD_String_xy(0,0,"HH:MM");
	LCD_String_xy(1,0,"^");
	LCD_String_xy(1,9,"B>BACK");
}

void LCD_SetTime_H2(const char *H1)
{
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,"H:MM");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,1,"^");
	LCD_String_xy(1,9,"B>RESET");
}


void LCD_SetTime_M1(const char *H1,const char *H2)
{
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":MM");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,3,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetTime_M2(const char *H1,const char *H2,const char *M1)
{
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":");
	strcat(time,M1);
	strcat(time,"M");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,4,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetTime_Final(const char *H1,const char *H2,const char *M1,const char *M2)
{
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":");
	strcat(time,M1);
	strcat(time,M2);
	LCD_String_xy(0,0,time);
	LCD_String_xy(0,9,"A>SET");
	LCD_String_xy(1,9,"B>RESET");
}

////////////////
//SETTING DATE//
////////////////

void LCD_SetDate_Y1()
{
	LCD_Clear();
	LCD_String_xy(0,0,"YY/MM/DD");
	LCD_String_xy(1,0,"^");
	LCD_String_xy(1,9,"B>BACK");
}

void LCD_SetDate_Y2(const char *Y1)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,"Y/MM/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,1,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetDate_M1(const char *Y1,const char *Y2)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/MM/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,3,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetDate_M2(const char *Y1,const char *Y2,const char *M1)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/");
	strcat(date,M1);
	strcat(date,"M/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,4,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetDate_D1(const char *Y1,const char *Y2,const char *M1,const char *M2)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/");
	strcat(date,M1);
	strcat(date,M2);
	strcat(date,"/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,6,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetDate_D2(const char *Y1,const char *Y2,const char *M1,const char *M2,const char *D1)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/");
	strcat(date,M1);
	strcat(date,M2);
	strcat(date,"/");
	strcat(date,D1);
	strcat(date,"D");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,7,"^");
	LCD_String_xy(1,9,"B>RESET");
}

void LCD_SetDate_Final(const char *Y1,const char *Y2,const char *M1,const char *M2,const char *D1,const char *D2)
{
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/");
	strcat(date,M1);
	strcat(date,M2);
	strcat(date,"/");
	strcat(date,D1);
	strcat(date,D2);
	LCD_String_xy(0,0,date);
	LCD_String_xy(0,9,"A>SET");
	LCD_String_xy(1,9,"B>RESET");
}

#endif /* LCD_H_ */