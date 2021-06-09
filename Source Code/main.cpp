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

// initializing global variables
DS3231 RTC(SDA,SCL);
Alarm alarm1,alarm2,alarm3,alarm4;
Alarm alarm_list[4] = {alarm1,alarm2,alarm3,alarm4};

// function prototypes
void Alarm_Options(Alarm *alarm_list,int i);
void Alarm_Menu();
void Set_Time_Menu();
void Menu();

int main(void)
{
    RTC.begin();
	LCD_Init();
	
	int menu;
	
	while (1) 
    {
		Time t = RTC.getTime();			// get the current time as a Time object
		
		LCD_Home(RTC);					
		
		// check if any alarm time has reached
		for (int i = 0; i < 4; i++)		// iterating through each alarm
		{
			if ((t.hour == alarm_list[i].hour) && (t.min == alarm_list[i].minute) && (alarm_list[i].active == 1))	// check for ring time of an active alarm
				alarm_list[i].ring();
				break;
		}
		
		LCD_Home(RTC);
		
		menu = menu_read();				// check if menu button is pressed
		
		if (menu == 1)
			Menu();						// execute menu function
    }
}

// Main menu function
void Menu()
{
	LCD_Menu();
	
	int input = Keypad_read();
	
	switch (input)
	{
		case 1:		// Set Time and Date
			Set_Time_Menu();
			break;
		case 2:		// Set Alarm
			Alarm_Menu();
			break;
		case 3:		// Reset the clock
			reset_time(RTC);
			timing_delete_alarms(alarm_list);
			break;
		case 4:		// Back
			return;
		default:	// None of the above (invalid input)
			LCD_Invalidinput();
			_delay_ms(1000);
			Menu();	// Call Menu function recursively
	}
	return;
}

// Set Time Menu function
void Set_Time_Menu()
{
	LCD_SetTimeMenu();
	
	int input = Keypad_read();
	
	switch (input)
	{
		case 1:		// Set Time
			timing_set_time(RTC);
			break;
		case 2:		// Set Date
			timing_set_date(RTC);
			break;
		case 3:		// Back (base case of the recursive function)
			Menu();
			return;
		default:	// invalid input
			LCD_Invalidinput();
			_delay_ms(1000);
			break;
	}
	
	Set_Time_Menu();	// navigate back to Set Time Menu after each setting except Back
	return;
}

void Alarm_Menu()
{	 
	// Write code for scrolling 
	LCD_AlarmList(alarm_list);	// Add a Back
	
	int input = Keypad_read();
	
	if (input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7) // if the user has selected an alarm
		Alarm_Options(alarm_list,input);
		
	else if (input == 10)	// Back
	{
		Menu();
		return;
	}
	else	// invalid input
	{
		LCD_Invalidinput();
		_delay_ms(1000);
		Alarm_Menu();
	}
	
	return;
}

void Alarm_Options(Alarm *alarm_list,int i)
{
	LCD_AlarmMenu();
	
	int input = Keypad_read();
	
	switch (input)
	{
		case 1:	 // Set
			timing_set_alarm(alarm_list,i);
			break;
		case 2:	 // Delete
			alarm_list[i].del();;
			break;
		case 3:	 // Set Tone
			alarm_list[i].set_tone();
			break;
		case 4:	 // Back
			Alarm_Menu();
			return;
		default: // invalid input
			LCD_Invalidinput();
			_delay_ms(1000);
			break;
	}
	
	Alarm_Options(alarm_list,i);
	return;
}

