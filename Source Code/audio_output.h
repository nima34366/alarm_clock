/*
 * audio_output.h
 *
 * Created: 6/5/2021 7:48:23 PM
 *  Author: User
 */ 
#ifndef AUDIO_OUTPUT_H_
#define AUDIO_OUTPUT_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "notes.h"
#include "tones.h"
static int stop_audio;
static int check_input_pin;
static float Note_frequency;
static float Note_duration;
#define PORT PORTC
#define PIN_SPEAKER_OUT PINC0  //speaker port
#define PIN_STOP_ALARM PINC2

class Tones
{
	public:
	Tones();
	int *notes;
	int *durations;
	int length;
	int rate;
	inline void play_note(float Note_frequency,float Note_duration);
	inline void audio_play();
	
};

#endif

