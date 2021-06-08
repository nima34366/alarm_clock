/*
 * Alarm_Clock.cpp
 *
 * Created: 6/8/2021 1:40:08 AM
 * Author : Chathuni
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "lcd.h"
#include "keypad.h"
#include "alarm_timing.h"

#define SDA PINC4
#define SCL PINC5

DS3231 RTC(SDA,SCL);
Alarm alarm1,alarm2,alarm3,alarm4;
Alarm alarm_list[4] = {alarm1,alarm2,alarm3,alarm4};

void Set_Time_Menu();
void Menu();

int main(void)
{
    RTC.begin();
	LCD_Init();
	
	int menu;
	
	while (1) 
    {
		Time t = RTC.getTime();
		
		LCD_Home(RTC);
		
		for (int i = 0; i < 4; i++)
		{
			if ((t.hour == alarm_list[i].hour) && (t.min == alarm_list[i].minute) && (alarm_list[i].active == 1))
				alarm_list[i].ring();
		}
		
		LCD_Home(RTC);
		
		menu = menu_read();
		
		if (menu == 1)
			Menu();
    }
}

void Menu()
{
	LCD_Menu();
	
	int input = Keypad_read();
	
	switch (input)
	{
		case 1:
			Set_Time_Menu();
			break;
		case 2:
			//Alarm_menu();
			break;
		case 3:
			// Write time reset
			timing_delete_alarms(alarm_list);
			break;
		case 4:
			return;
		default:
			LCD_Invalidinput();
			_delay_ms(1000);
			Menu();
	}
	
	return;
}

void Set_Time_Menu()
{
	LCD_SetTimeMenu();
	
	int input = Keypad_read();
	
	switch (input)
	{
		case 1:
			timing_set_time(RTC);
			break;
		case 2:
			timing_set_date(RTC);
			break;
		case 3:
			Menu();
			return;
		default:
			LCD_Invalidinput();
			_delay_ms(1000);
			break;
	}
	
	Set_Time_Menu();
	return;
}

