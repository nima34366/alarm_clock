/*
 * Alarm_timing.cpp
 *
 * Created: 5/11/2021 11:27:18 AM
 *  Author: Chathuni
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "Alarm_timing.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#ifndef TWI_FREQ
#define TWI_FREQ 400000L
#endif


#define REG_SEC		0x00
#define REG_MIN		0x01
#define REG_HOUR	0x02
#define REG_DOW		0x03
#define REG_DATE	0x04
#define REG_MON		0x05
#define REG_YEAR	0x06
#define REG_CON		0x0e
#define REG_STATUS	0x0f
#define REG_AGING	0x10
#define REG_TEMPM	0x11
#define REG_TEMPL	0x12

#define DS3231_ADDR_R	0xD1
#define DS3231_ADDR_W	0xD0
#define DS3231_ADDR		0x68  

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#define SDA PINC4
#define SCL PINC5

////////////////////////////////////////////////////////
/*************** Class methods for Time ***************/
////////////////////////////////////////////////////////
Time::Time()
{
	this->year = 2021;
	this->mon  = 5;
	this->date = 28;
	this->hour = 0;
	this->min  = 0;
	this->sec  = 0;
	this->dow  = 3;
}

////////////////////////////////////////////////////////
/************** Class methods for DS3231 **************/
////////////////////////////////////////////////////////
DS3231::DS3231(uint8_t data_pin, uint8_t sclk_pin)
{
	_sda_pin = data_pin;
	_scl_pin = sclk_pin;
}

void DS3231::begin()
{
	// activate internal pullups for twi.
	PORTC |= (1<<SDA);
	PORTC |= (1<<SCL);

	// initialize twi prescalar and bit rate
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;

	// enable twi module and twi interrupt
	TWCR = _BV(TWEN) | _BV(TWIE);
}

void DS3231::_burstRead()
{
	// Send start address
	TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = DS3231_ADDR_W;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = 0;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

	// Read data starting from start address
	TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = DS3231_ADDR_R;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	for (int i=0; i<7; i++)
	{
		TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);								// Send ACK and clear TWINT to proceed
		while ((TWCR & _BV(TWINT)) == 0) {};									// Wait for TWI to be ready
		_burstArray[i] = TWDR;
	}
	TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

	TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
}

void DS3231::_writeRegister(uint8_t reg, uint8_t value)
{
	// Send start address
	TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = DS3231_ADDR_W;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = reg;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = value;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

	TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
}

Time DS3231::getTime()
{
	Time t;
	_burstRead();
	t.sec	= _decode(_burstArray[0]);
	t.min	= _decode(_burstArray[1]);
	t.hour	= _decodeH(_burstArray[2]);
	t.dow	= _burstArray[3];
	t.date	= _decode(_burstArray[4]);
	t.mon	= _decode(_burstArray[5]);
	t.year	= _decodeY(_burstArray[6])+2000;
	return t;
}

void DS3231::setTime(uint8_t hour, uint8_t min, uint8_t sec)
{
	if (((hour>=0) && (hour<24)) && ((min>=0) && (min<60)) && ((sec>=0) && (sec<60)))
	{
		_writeRegister(REG_HOUR, _encode(hour));
		_writeRegister(REG_MIN, _encode(min));
		_writeRegister(REG_SEC, _encode(sec));
	}
}

void DS3231::setDate(uint8_t date, uint8_t mon, uint16_t year)
{
	if (((date>0) && (date<=31)) && ((mon>0) && (mon<=12)) && ((year>=2000) && (year<3000)))
	{
		year -= 2000;
		_writeRegister(REG_YEAR, _encode(year));
		_writeRegister(REG_MON, _encode(mon));
		_writeRegister(REG_DATE, _encode(date));
	}
}

char *DS3231::getTimeStr()
{
	static char output[] = "xxxxxx"; // initializing char array
	Time t;
	t = getTime();
	
	// convert hour to string
	if (t.hour<10)
		output[0]=48;				// ASCII 0
	else
		output[0]=char((t.hour / 10)+48);
		
	output[1]=char((t.hour % 10)+48);
	output[2]=58;					// ASCII :
	
	// convert minute to string
	if (t.min<10)
		output[3]=48;
	else
		output[3]=char((t.min / 10)+48);
		
	output[4]=char((t.min % 10)+48);
	output[5]=58;
	output[5]=0;	// end of string
	
	return (char*)&output;
}

char *DS3231::getDateStr(char divider)
{
	static char output[] = "xxxxxxxxxx";	// initializing char array
	int yr;
	Time t;
	t=getTime();
	
	// convert date to string
	if (t.date<10)
		output[0]=48;
	else
		output[0]=char((t.date / 10)+48);
		
	output[1]=char((t.date % 10)+48);
	output[2]=divider;
	
	// convert month to string
	if (t.mon<10)
		output[3]=48;
	else
		output[3]=char((t.mon / 10)+48);
		
	output[4]=char((t.mon % 10)+48);
	output[5]=divider;
	
	// convert year to string
	yr=t.year;
	output[6]=char((yr / 1000)+48);
	output[7]=char(((yr % 1000) / 100)+48);
	output[8]=char(((yr % 100) / 10)+48);
	output[9]=char((yr % 10)+48);
	output[10]=0; // end of string
	
	return (char*)&output;
}

// functions to convert hex representation to integer value
uint8_t	DS3231::_decode(uint8_t value)
{
	uint8_t decoded = value & 127;
	decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
	return decoded;
}

uint8_t DS3231::_decodeH(uint8_t value)
{
	if (value & 128)
	value = (value & 15) + (12 * ((value & 32) >> 5));
	else
	value = (value & 15) + (10 * ((value & 48) >> 4));
	return value;
}

uint8_t	DS3231::_decodeY(uint8_t value)
{
	uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
	return decoded;
}

// functions to convert integer value to hex representation to write to registers
uint8_t DS3231::_encode(uint8_t value)
{
	uint8_t encoded = ((value / 10) << 4) + (value % 10);
	return encoded;
}

////////////////////////////////////////////////////////////
/****************** Class methods of Alarm ****************/
////////////////////////////////////////////////////////////
Alarm::Alarm()
{
	this->hour = 0;
	this->minute = 0;
	this->active = 0;
	this->tone = Tones();	// default tone
}

// Public functions

void Alarm::set(int alarm_h,int alarm_m)
{
	// setting the alarm and activating
	this->hour = alarm_h;
	this->minute = alarm_m;
	this->active = 1;
}

void Alarm::del()
{
	this->active = 0;  
}

void Alarm::ring()
{
	LCD_Ringing();
	Tones alarm_tone = this->tone;
	alarm_tone.audio_play();
	
	// Done ringing
	this->active = 0;
}

void Alarm::set_tone(Tones tone_selected)
{
	this->tone = tone_selected;
}

/////////////////////////////////////////////////////////////
/************* Common function definitions******************/
/////////////////////////////////////////////////////////////
void timing_set_time(DS3231 rtc)
{
	// local variables
	int h1,h2;
	int m1,m2;
	
	int time_h;
	int time_m;
	
	// read digit 1 of hour
	LCD_SetTime_H1();
	h1 = Keypad_read();
	if (h1==20)			// input == 20 --> Back
	{
		return;
	}
	
	LCD_SetTime_H2(h1);
	h2 = Keypad_read();
	if (h2==20)					// input == 20 --> Reset
	{
		timing_set_time(rtc);	// calling the function again recursively
		return;
	}
	
	LCD_SetTime_M1(h1,h2);
	m1 = Keypad_read();
	if (m1==20)					// input == 20 --> Reset
	{
		timing_set_time(rtc);
		return;
	}
	
	LCD_SetTime_M2(h1,h2,m1);
	m2 = Keypad_read();
	if (m2==20)					// input == 20 --> Reset
	{
		timing_set_time(rtc);
		return;
	}
	
	LCD_SetTime_Final(h1,h2,m1,m2);
	int confirm = Keypad_read();
	
	// confirm = 10 --> Set, confirm = 20 --> Reset
	while (!(confirm == 10 || confirm == 20))	// loop until a valid input is given
	{
		LCD_Invalidinput();
		_delay_ms(1000);
		LCD_SetTime_Final(h1,h2,m1,m2);
		confirm = Keypad_read();
	}
	
	if (confirm == 10){
		//setting the time
		time_h = h1*10+h2;
		time_m = m1*10+m2;
		if (!(((0 <= time_h) && (time_h <= 24)) && ((0 <= time_m) && (time_m <=60)))){		// if the inputs are invalid
			LCD_Invalidinput();
			_delay_ms(1000);
			timing_set_time(rtc);
			return;
		}
		rtc.setTime(time_h,time_m,0);		// Set Time in the RTC
	}
	else if (confirm == 20)
	{
		timing_set_date(rtc);
		return;
	}
}

void timing_set_date(DS3231 rtc)
{
	// initializing local variables
	int y1,y2;
	int m1,m2;
	int d1,d2;
	
	int year,month,day;
	
	LCD_SetDate_Y1();	
	y1 = Keypad_read();
	if (y1==20)	// Back
	{
		return;
	}
	
	LCD_SetDate_Y2(y1);	
	y2 = Keypad_read();
	if (y2==20)			// Reset
	{
		timing_set_date(rtc);
		return;
	}
	
	LCD_SetDate_M1(y1,y2);	
	m1 = Keypad_read();
	if (m1==20)			// Reset
	{
		timing_set_date(rtc);
		return;
	}
	
	LCD_SetTime_M2(y1,y2,m1);	
	m2 = Keypad_read();
	if (m2==20)			// Reset
	{
		timing_set_date(rtc);
		return;
	}
	
	LCD_SetDate_D1(y1,y2,m1,m2);	
	d1 = Keypad_read();
	if (d1==20)			// Reset
	{
		timing_set_date(rtc);
		return;
	}
	
	LCD_SetDate_D2(y1,y2,m1,m2,d1);
	d2 = Keypad_read();	
	if (d2==20)			// Reset
	{
		timing_set_date(rtc);
		return;
	}
	
	LCD_SetDate_Final(y1,y2,m1,m2,d1,d2);	
	int confirm = Keypad_read();
	
	// confirm = 10 --> Set, confirm = 20 --> Reset
	while (!(confirm == 10 || confirm == 20))		// Loop until invalid input
	{
		LCD_Invalidinput();
		_delay_ms(1000);
		LCD_SetDate_Final(y1,y2,m1,m2,d1,d2);	//replace
		confirm = Keypad_read();
	}
	
	if (confirm == 10){		// Set
		//setting the date
		year = 2000 + y1*10 + y2;
		month = m1*10 + m2;
		day = d1*10 + d2;
	
		if (!(((0 <= month) && (month <= 12)) && ((0 <= day) && (day <= 31)))){		// if the inputs are invalid
			LCD_Invalidinput();
			_delay_ms(1000);
			timing_set_date(rtc);		// Recall Set Date function again
			return;
		}
		rtc.setDate(day,month,year);
	}
	else if (confirm == 20)	// Reset
	{
		timing_set_date(rtc);
		return;
	}
	_delay_ms(100);
}

void timing_set_alarm(Alarm alarm)
{
	// initializing local variables
	int h1,h2;
	int m1,m2;
	
	int h,m;
	
	LCD_SetTime_H1();
	h1 = Keypad_read();
	if (h1==20)
	{
		return;
	}	
	
	LCD_SetTime_H2(h1);
	h2 = Keypad_read();
	if (h2==20)
	{
		timing_set_alarm(alarm);
		return;
	}
	
	LCD_SetTime_M1(h1,h2);
	m1 = Keypad_read();
	if (m1==20)
	{
		timing_set_alarm(alarm);
		return;
	}
	
	LCD_SetTime_M2(h1,h2,m1);
	m2 = Keypad_read();
	if (m2==20)
	{
		timing_set_alarm(alarm);
		return;
	}
	
	LCD_SetTime_Final(h1,h2,m1,m2);
	int confirm = Keypad_read();
	
	while (!(confirm == 10 || confirm == 20))
	{
		LCD_Invalidinput();
		_delay_ms(1000);
		LCD_SetTime_Final(h1,h2,m1,m2);
		confirm = Keypad_read();
	}
	
	if (confirm == 10){
		//setting the time
		h = h1*10+h2;
		m = m1*10+m2;
		if (!(((0 <= h) && (h <= 24)) && ((0 <= m) && (m <=60)))){		// if the inputs are invalid
			LCD_Invalidinput();
			_delay_ms(1000);
			timing_set_alarm(alarm);
			return;
		}
		alarm.set(h,m);
	}
	else if (confirm == 20)
	{
		timing_set_alarm(alarm);
		return;
	}
	_delay_ms(100);
}

void timing_delete_alarms(Alarm *alarm_list)
{
	int length = sizeof(alarm_list);		// Memory Size of all the alarms
	int step = sizeof(Alarm);				// Memory of a single alarm
	int n = length/step;					// Number of alarms
	
	for (int i = 0; i < n; i++)
	{
		alarm_list[i].del();
	}
}



