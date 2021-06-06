
/*
 * audio_output.h
 *
 * Created: 6/5/2021 7:48:23 PM
 *  Author: User
 */ 
#define audio_output_h
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "notes.h"
#include "tones.h"
int stop_audio;
int check_input_pin;
float Note_frequency;
float Note_duration;
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
	void play_note(float Note_frequency, float Note_duration);
	void audio_play();
	
};

