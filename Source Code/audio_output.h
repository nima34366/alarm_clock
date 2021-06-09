/*
 * audio_output.h
 *
 * Created: 6/5/2021 7:48:23 PM
 *  Author: User
 */ 
#ifndef AUDIO_OUTPUT_H_
#define AUDIO_OUTPUT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "notes.h"
#include "tones.h"
#define PORT PORTC
#define PIN_SPEAKER_OUT PINC2  //speaker port
#define PIN_STOP_ALARM PINC3

class Tones
{
	public:
	Tones();
	int *notes;
	int *durations;
	int length;
	int rate;
	void play_note(float Note_frequency,float Note_duration);
	void audio_play();
	
};

#endif
