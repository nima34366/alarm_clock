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

// LEDs
#define AlarmActiveLED PIND0
#define AlarmRingLED PIND1
#define SetTimeLED PIND2
#define SetAlarmLED PIND3
#define SetHourLED PIND5
#define SetMinuteLED PIND4

#define BitPin PINB

// Switches for mode selection
#define SetTime PINC0
#define SetAlarm PINC1
#define Snooze PINC2

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
	void	begin();
	Time	getTime();
	void	setTime(uint8_t hour, uint8_t min, uint8_t sec);

	private:
	uint8_t _scl_pin;
	uint8_t _sda_pin;
	uint8_t _burstArray[7];

	
	void	_burstRead();
	uint8_t	_readRegister(uint8_t reg);
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
	
	Alarm();
	void set();
	void del();
	void ring();
};

// Function  prototypes
unsigned char reverse(unsigned char b);
int read_digit();
void Alarm_timing_init();
void Alarm_timing_set_time(DS3231 rtc);

#endif /* ALARM_TIMING_H_ */