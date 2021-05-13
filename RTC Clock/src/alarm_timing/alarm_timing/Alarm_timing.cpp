/*
 * Alarm_timing.cpp
 *
 * Created: 5/11/2021 11:27:18 AM
 *  Author: Chathuni
 */ 

#include "Alarm_timing.h"

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

#define SEC_1970_TO_2000 946684800

#define DS3231_ADDR_R	0xD1
#define DS3231_ADDR_W	0xD0
#define DS3231_ADDR		0x68  

#define _BV(n) (1 << n)
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#define SDA PINC4
#define SCL PINC5

// Class methods for Time
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

// Class methods for DS3231
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
	//delay(1);  // Workaround for a linker bug

	// initialize twi prescalar and bit rate
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;

	// enable twi module, acks, and twi interrupt
	TWCR = _BV(TWEN) | _BV(TWIE)/* | _BV(TWEA)*/;
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

uint8_t DS3231::_encode(uint8_t value)
{
	uint8_t encoded = ((value / 10) << 4) + (value % 10);
	return encoded;
}
