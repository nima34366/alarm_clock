/*
 * keypad.c
 *
 * Created: 2021-06-01 12:07:45 AM
 *  Author: Thilanka Rajaka
 */
#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"
 
int keypd(int *key1, int *key2)
{
	DDRC = 0b00000111;    /* pc0,pc1,pc2 set as output */
	PORTC = 0b00111000;   /* pc0-pc2 outputs turn on (HIGH)*/
	*key2 = PINC & 0b00000111 ;
	
	DDRC = 0b00111000;    /* pc3,pc4,pc5 set as output */
	PORTC = 0b00000111;   /* pc0-pc2 outputs turn on (HIGH)*/
	*key1 = PINC & 0b00111000 ;
	return 0;
}