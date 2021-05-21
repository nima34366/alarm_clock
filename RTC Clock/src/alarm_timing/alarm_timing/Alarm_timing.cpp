/*
 * Alarm_timing.cpp
 *
 * Created: 5/11/2021 11:27:18 AM
 *  Author: Chathuni
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
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

/*************** Class methods for Time ***************/
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

/************** Class methods for DS3231 **************/
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

uint8_t DS3231::_readRegister(uint8_t reg)
{
	uint8_t	readValue=0;

	// Send start address
	TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send START
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = DS3231_ADDR_W;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = reg;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

	// Read data starting from start address
	TWCR = _BV(TWEN) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTA);						// Send rep. START
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWDR = DS3231_ADDR_R;
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWEA);									// Send ACK and clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready
	readValue = TWDR;
	TWCR = _BV(TWEN) | _BV(TWINT);												// Send NACK and clear TWINT to proceed
	while ((TWCR & _BV(TWINT)) == 0) {};										// Wait for TWI to be ready

	TWCR = _BV(TWEN)| _BV(TWINT) | _BV(TWSTO);									// Send STOP
	return readValue;
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


/****************** Class methods of Alarm ****************/
Alarm::Alarm()
{
	this->hour = 0;
	this->minute  = 0;
	this->active  = 0;
}

// Public functions

void Alarm::set()
{
	PORTD |= (1<<SetAlarmLED); // turning on set alarm LED
	_delay_ms(500);
	
	int alarm_h;
	int alarm_m;
	int set_alarm_input;
	
	PORTD |= (1<<SetHourLED); // turning on set hour LED
	
	// wait until user presses set alarm button to read the hours
	while (1)
	{
		set_alarm_input = PINC & (1<<SetAlarm);
		if (set_alarm_input > 0)
		{
			alarm_h = read_digit();
			break;
		}
		_delay_ms(100);
	}
	
	PORTD &= ~(1<<SetHourLED); // turning off set hour LED
	_delay_ms(500);
	
	PORTD |= (1<<SetMinuteLED); // turning on set minute LED
	
	// wait until user presses set alarm button to read the minutes
	while (1)
	{
		set_alarm_input = PINC & (1<<SetAlarm);
		if (set_alarm_input > 0)
		{
			alarm_m = read_digit();
			break;
		}
		_delay_ms(100);
	}
	
	PORTD &= ~(1<<SetMinuteLED); // turning off set minute LED
	
	// setting the alarm and activating
	this->hour = alarm_h;
	this->minute = alarm_m;
	this->active = 1;
	
	PORTD |= (1<<AlarmActiveLED); // turning on active alarm indicative LED
	PORTD &= ~(1<<SetAlarmLED); // turning off set alarm LED
	_delay_ms(500);
	
}

void Alarm::del()
{
	this->active = 0;
	PORTD &= ~(1<<AlarmActiveLED); // turning off active alarm indicative LED
	_delay_ms(500);
}

void Alarm::ring()
{
	PORTD |= (1<<AlarmRingLED); // turning on alarm ring indicative LED
	
	int snooze_input = 0;
	
	// wait for the button press of snooze to stop the ringing
	while (1)
	{
		snooze_input = PINC & (1<<Snooze); // reading the state of snooze button
		if (snooze_input > 0)
		{
			PORTD &= ~(1<<AlarmRingLED); // turning off alarm ring indicative LED
			break;
		}
		_delay_ms(100);
	}
	
	this->active = 0;
	PORTD &= ~(1<<AlarmActiveLED); // turning off active alarm indicative LED
}

// Common function definitions

// Reverse the order of a byte
unsigned char reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

int read_digit()
{
	int bit_input = BitPin % (0b00111111);
	int number = reverse(bit_input<<2); // manipulating the input to obtain the integer
	return number;
}

void Alarm_timing_init()
{
	// setting pins as input/output
	
	DDRD = 0xff;	// PortD contains only the LEDs, setting them as outputs
	PORTD = 0x00;	// turning off the LEDs as initial conditions
	
	DDRB = 0x00;	// PortB contains only the inputs of bit pattern
	
	DDRC &= ~((1<<SetTime) | (1<<SetAlarm) | (1<<Snooze));
}

void Alarm_timing_set_time(DS3231 rtc)
{
	PORTD |= (1<<SetTimeLED); // turning on set time LED
	_delay_ms(500);
	
	int time_h;
	int time_m;
	int set_time_input;
	
	PORTD |= (1<<SetHourLED); // turning on set hour LED
	
	// wait until user presses set time button to read the hours
	while (1)
	{
		set_time_input = PINC & (1<<SetTime);
		if (set_time_input > 0)
		{
			time_h = read_digit();
			break;
		}
		_delay_ms(100);
	}
	
	PORTD &= ~(1<<SetHourLED); // turning off set hour LED
	_delay_ms(500);
	
	PORTD |= (1<<SetMinuteLED); // turning on set minute LED
	
	// wait until user presses set time button to read the minutes
	while (1)
	{
		set_time_input = PINC & (1<<SetTime);
		if (set_time_input > 0)
		{
			time_m = read_digit();
			break;
		}
		_delay_ms(100);
	}
	
	//setting the time
	rtc.setTime(time_h,time_m,0);
	
	PORTD &= ~(1<<SetTimeLED); // turning off set time LED
	PORTD &= ~(1<<SetMinuteLED); // turning off set minute LED
	
	_delay_ms(500);
}