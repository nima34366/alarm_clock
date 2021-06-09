/*
 * Alarm_timing.h
 *
 * Created: 5/11/2021 11:25:49 AM
 *  Author: Chathuni
 */ 


#ifndef ALARM_TIMING_H_
#define ALARM_TIMING_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "audio_output.h"			// Audio Output Header

// Class for Time
class Time
{
	public:
	uint8_t		hour;
	uint8_t		min;
	uint8_t		sec;
	uint8_t		date;
	uint8_t		mon;
	uint16_t	year;
	uint8_t		dow;

	Time();
};

// Class for DS3231
class DS3231
{
	public:
	DS3231(uint8_t data_pin, uint8_t sclk_pin);
	void	begin();												// Begin I2C communication
	Time	getTime();												// to get the current time as type Time
	void	setTime(uint8_t hour, uint8_t min, uint8_t sec);		// to set time in the rtc
	void	setDate(uint8_t date, uint8_t mon, uint16_t year);		// to set date in the rtc
	char	*getTimeStr();											// to get time as a string in "hh:mm" format
	char	*getDateStr(char divider='/');							// to get date as a string in format "dd/mm/yyyy"

	private:
	uint8_t _scl_pin;
	uint8_t _sda_pin;
	uint8_t _burstArray[7];

	
	void	_burstRead();
	void 	_writeRegister(uint8_t reg, uint8_t value);
	uint8_t	_decode(uint8_t value);
	uint8_t	_decodeH(uint8_t value);
	uint8_t	_decodeY(uint8_t value);
	uint8_t	_encode(uint8_t vaule);
};

// Class for Alarm
class Alarm
{
public:
	int hour;
	int minute;
	int active;
	Tones tone;														// Class from audio
	
	Alarm();
	void set(int alarm_h,int alarm_m);								// set an alarm
	void del();														// delete the instance of alarm by setting active->0
	void ring();													// ring the alarm
 	void set_tone();										// set a tone for the alarm
	char *getAlarmStr();										// get the alarm as a string
};

// Function  prototypes
void timing_set_time(DS3231 rtc);									// Main function to set time
void timing_set_date(DS3231 rtc);									// Main function to set date
void timing_set_alarm(Alarm *alarm_list,int i);						// Main function to set an alarm
void timing_delete_alarms(Alarm *alarm_list);						// to delete all the alarms
void reset_time(DS3231 rtc);										// to reset time

#endif /* ALARM_TIMING_H_ */