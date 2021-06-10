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
#include <stdio.h>
#include "alarm_timing.h"

#define LCD_Dir  DDRA			/* Define LCD data port direction */
#define LCD_Port PORTA			/* Define LCD data port */
#define RS PA0				/* Define Register Select pin */
#define EN PA1 				/* Define Enable signal pin */

inline const char *int_string(int a,char b[])
{
	sprintf(b,"%d",a);
	return b;
}

inline void LCD_Command( unsigned char cmnd )
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


inline void LCD_Char( unsigned char data )
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

inline void LCD_Init (void)			/* LCD Initialize function */
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


inline void LCD_String (const char* str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

inline void LCD_String_xy (char row, char pos,const char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

inline void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}

/////////////////////
//CENTRAL FUNCTIONS//
/////////////////////

inline void LCD_Home(DS3231 RTC,int prev_h,int prev_m)
{
	Time t = RTC.getTime();
	if (!(prev_h == t.hour && prev_m == t.min))
	{
		const char *Time_str = RTC.getTimeStr();
		const char *Date_str = RTC.getDateStr();
		LCD_Clear();
		LCD_String_xy(0,6,Time_str);
		LCD_String_xy(1,4,Date_str);
	}
}

inline void LCD_Menu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>D&T");
	LCD_String_xy(0,8,"2>ALARM");
	LCD_String_xy(1,0,"3>RESET");
	LCD_String_xy(1,8,"4>BACK");
}

inline void LCD_Invalidinput()
{
	LCD_Clear();
	LCD_String_xy(0,1,"INVALID INPUT");
}

inline void LCD_SetTimeMenu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>TIME");
	LCD_String_xy(0,8,"2>DATE");
	LCD_String_xy(1,0,"3>BACK");
}

inline void LCD_AlarmList(Alarm *alarms) 
{
	const char *alarm1_str,*alarm2_str,*alarm3_str,*alarm0_str;
	alarm0_str = alarms[0].getAlarmStr();
	alarm1_str = alarms[1].getAlarmStr();
	alarm2_str = alarms[2].getAlarmStr();
	alarm3_str = alarms[3].getAlarmStr();
	LCD_Clear();
	char alarm0[10]= "1>";
	char alarm1[10]= "2>";
	char alarm2[10]= "3>";
	char alarm3[10]= "4>"; 
	strcat(alarm0,alarm0_str);
	strcat(alarm1,alarm1_str);
	strcat(alarm2,alarm2_str);
	strcat(alarm3,alarm3_str);
	LCD_String_xy(0,0,alarm0);
	LCD_String_xy(0,8,alarm1);
	LCD_String_xy(1,0,alarm2);
	LCD_String_xy(1,8,alarm3);
}

inline void LCD_AlarmMenu()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>SET");
	LCD_String_xy(0,8,"2>DELETE");
	LCD_String_xy(1,0,"3>TONE");
	LCD_String_xy(1,8,"4>BACK");
}

inline void LCD_Tone()
{
	LCD_Clear();
	LCD_String_xy(0,0,"1>STARW");
	LCD_String_xy(0,8,"2>HARRYP");
	LCD_String_xy(1,0,"3>GOT");
	LCD_String_xy(1,8,"4>GREENL");
}

inline void LCD_Ringing()
{
	LCD_Clear();
	LCD_String_xy(0,6,"WAKE");
	LCD_String_xy(1,7,"UP");
}

////////////////
//SETTING TIME//
////////////////

inline void LCD_SetTime_H1()
{
	LCD_Clear();
	LCD_String_xy(0,0,"HH:MM");
	LCD_String_xy(1,0,"^");
	LCD_String_xy(1,9,"*>BACK");
}

inline void LCD_SetTime_H2(int h1)
{
	char H1[5]="";
	sprintf(H1,"%d",h1);
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,"H:MM");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,1,"^");
	LCD_String_xy(1,9,"*>RESET");
}


inline void LCD_SetTime_M1(int h1,int h2)
{
	char H1[5]="";
	char H2[5]="";
	sprintf(H1,"%d",h1);
	sprintf(H2,"%d",h2);
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":MM");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,3,"^");
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetTime_M2(int h1,int h2,int m1)
{
	char H1[5]="";
	char H2[5]="";
	char M1[5]="";
	sprintf(H1,"%d",h1);
	sprintf(H2,"%d",h2);
	sprintf(M1,"%d",m1);
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":");
	strcat(time,M1);
	strcat(time,"M");
	LCD_String_xy(0,0,time);
	LCD_String_xy(1,4,"^");
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetTime_Final(int h1,int h2,int m1,int m2)
{
	char H1[5]="";
	char H2[5]="";
	char M1[5]="";
	char M2[5]="";
	sprintf(H1,"%d",h1);
	sprintf(H2,"%d",h2);
	sprintf(M1,"%d",m1);
	sprintf(M2,"%d",m2);
	LCD_Clear();
	char time[10]="";
	strcat(time,H1);
	strcat(time,H2);
	strcat(time,":");
	strcat(time,M1);
	strcat(time,M2);
	LCD_String_xy(0,0,time);
	LCD_String_xy(0,9,"#>SET");
	LCD_String_xy(1,9,"*>RESET");
}

////////////////
//SETTING DATE//
////////////////

inline void LCD_SetDate_Y1()
{
	LCD_Clear();
	LCD_String_xy(0,0,"YY/MM/DD");
	LCD_String_xy(1,0,"^");
	LCD_String_xy(1,9,"*>BACK");
}

inline void LCD_SetDate_Y2(int y1)
{
	char Y1[5]="";
	sprintf(Y1,"%d",y1);
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,"Y/MM/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,1,"^");
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetDate_M1(int y1,int y2)
{
	char Y1[5]="";
	char Y2[5]="";
	sprintf(Y1,"%d",y1);
	sprintf(Y2,"%d",y2);
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/MM/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,3,"^");
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetDate_M2(int y1,int y2,int m1)
{
	char Y1[5]="";
	char Y2[5]="";
	char M1[5]="";
	sprintf(Y1,"%d",y1);
	sprintf(Y2,"%d",y2);
	sprintf(M1,"%d",m1);
	LCD_Clear();
	char date[10]="";
	strcat(date,Y1);
	strcat(date,Y2);
	strcat(date,"/");
	strcat(date,M1);
	strcat(date,"M/DD");
	LCD_String_xy(0,0,date);
	LCD_String_xy(1,4,"^");
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetDate_D1(int y1,int y2,int m1,int m2)
{
	char Y1[5]="";
	char Y2[5]="";
	char M1[5]="";
	char M2[5]="";
	sprintf(Y1,"%d",y1);
	sprintf(Y2,"%d",y2);
	sprintf(M1,"%d",m1);
	sprintf(M2,"%d",m2);
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
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetDate_D2(int y1,int y2,int m1,int m2,int d1)
{
	char Y1[5]="";
	char Y2[5]="";
	char M1[5]="";
	char M2[5]="";
	char D1[5]="";
	sprintf(Y1,"%d",y1);
	sprintf(Y2,"%d",y2);
	sprintf(M1,"%d",m1);
	sprintf(M2,"%d",m2);
	sprintf(D1,"%d",d1);
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
	LCD_String_xy(1,9,"*>RESET");
}

inline void LCD_SetDate_Final(int y1,int y2,int m1,int m2,int d1,int d2)
{
	char Y1[5]="";
	char Y2[5]="";
	char M1[5]="";
	char M2[5]="";
	char D1[5]="";
	char D2[5]="";
	sprintf(Y1,"%d",y1);
	sprintf(Y2,"%d",y2);
	sprintf(M1,"%d",m1);
	sprintf(M2,"%d",m2);
	sprintf(D1,"%d",d1);
	sprintf(D2,"%d",d2);
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
	LCD_String_xy(0,9,"#>SET");
	LCD_String_xy(1,9,"*>RESET");
}

#endif /* LCD_H_ */