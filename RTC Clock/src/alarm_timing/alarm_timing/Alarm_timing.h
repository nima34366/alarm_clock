/*
 * Alarm_timing.h
 *
 * Created: 5/11/2021 11:25:49 AM
 *  Author: Chathuni
 */ 


#ifndef ALARM_TIMING_H_
#define ALARM_TIMING_H_

// LEDs
#define LEDPort PORTD
#define AlarmActiveLED PIND0
#define AlarmRingLED PIND1
#define SetTimeLED PIND3
#define SetAlarmLED PIND4
#define SetHourLED PIND6
#define SetMinuteLED PIND0

// Bits for number reading
#define Bit1 PINB0
#define Bit2 PINB1
#define Bit3 PINB2
#define Bit4 PINB3
#define Bit5 PINB4
#define Bit6 PINB5

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
void Alarm_timing_init();
void Alarm_timing_set_time();

#endif /* ALARM_TIMING_H_ */