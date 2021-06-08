#include "audio_output.h"

Tones::Tones()
{
	 this->notes=harry_potter_notes;
	 this->durations=harry_potter_notes_durations;
	 this->length=harry_potter_notes_length;
	 this->rate=4000;
}
	
void Tones::play_note(float Note_frequency,float Note_duration)
{
	long cycles;
	float complete_period;
	DDRC |= (1 << PIN_SPEAKER_OUT);
		
	if (Note_frequency==0)
	{
		PORT &= ~(1 << PIN_SPEAKER_OUT);
		_delay_us(Note_duration);
	}
	else
	{
		complete_period=(1/Note_frequency)*1000;
		cycles=Note_duration/(complete_period*2);
		for (int i=0;i<cycles;i++)
		{
			_delay_ms(complete_period/2);
			PORT |= (1 << PIN_SPEAKER_OUT);
			_delay_ms(complete_period/2);
			PORT &= ~(1 << PIN_SPEAKER_OUT);
		}
	}
}
void Tones::audio_play()
{
	int stop_audio;
	int check_input_pin;	
	DDRC &= ~(1 << PIN_STOP_ALARM);
	while (stop_audio==1)
	{  //when alarm okay set the variable to 1
		for (int i = 0; i <  length ; i = i + 1)
		{
			check_input_pin=(PINC & (1<< PIN_STOP_ALARM));
			if(check_input_pin != 0)
			{  
				stop_audio=0;
				break;
			}
			play_note(notes[i],(rate/abs(durations[i])));
		}
	}
}

