/*
 * alarm_timing.cpp
 *
 * Created: 5/11/2021 11:22:40 AM
 * Author : Chathuni
 */ 


#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "Alarm_timing.h"		// Local Library

#define SDA PINC4
#define SCL PINC5

DS3231 RTC(SDA,SCL);

int main(void)
{
	// initialing pins as inputs/outputs and setting initial values
	// function from library Alarm_timing
	int set_time_input = 0;
	int set_alarm_input = 0;

	Alarm alarm1;
	RTC.begin();
	
	Alarm_timing_init();
    
    while (1) 
    {
		// get the current time
		Time t = RTC.getTime();
		int h = t.hour;
		int m = t.min;
		
		// check if any mode button is pressed, if so execute respective function
		
		// set time
		set_time_input = PINC & (1<<SetTime); // status of the set time button; 0 -> not pressed , otherwise -> pressed
		if (set_time_input > 0)	Alarm_timing_set_time(RTC);	// the button is pressed
		
		
		// set new alarm
		set_alarm_input = PINC & (1<<SetAlarm); // state of the set alarm button; 0 -> not pressed , otherwise -> pressed
		
		// if set alarm is pressed without a current active alarm --> set new alarm
		if (set_alarm_input > 0 && alarm1.active == 0)
		{
			alarm1.set();
		}
		
		set_alarm_input = PINC & (1<<SetAlarm); // state of the set alarm button; 0 -> not pressed , otherwise -> pressed
		
		// if set alarm is pressed with a current active alarm --> delete the current alarm
		if (set_alarm_input > 0 && alarm1.active == 1)
		{
			alarm1.del();
		}
		
		
		// check for alarm time
		if (alarm1.hour == h && alarm1.minute == m && alarm1.active == 1)
		{
			alarm1.ring();
		}
		
		_delay_ms(100);
		
    }
	return 0;
}

