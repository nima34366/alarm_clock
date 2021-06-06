#include "audio_output.h"

Tones::Tones()
{
	 notes=harry_potter_notes;
	 durations=harry_potter_notes_durations;
	 length=harry_potter_notes_length;
	 rate=4000;
}
	
void Tones::play_note(float Note_frequency, float Note_duration)
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


int main(void)
{
		
	Tones harry_potter;
	harry_potter.notes= harry_potter_notes;
	harry_potter.durations= harry_potter_notes_durations;
	harry_potter.length=harry_potter_notes_length;
	harry_potter.rate=4000;
	
	Tones game_of_throns;
	game_of_throns.notes=game_of_throns_notes;
	game_of_throns.durations=game_of_throns_notes_durations;
	game_of_throns.length=game_of_throns_notes_length;
	game_of_throns.rate=12000;
	
	Tones starwars;
	starwars.notes=starwars_notes;
	starwars.durations=starwars_notes_durations;
	starwars.length=starwars_notes_length;
	starwars.rate=6000;
	
	Tones greendleves;
	greendleves.notes=Greendleves_notes;
	greendleves.durations=game_of_throns_notes_durations;
	greendleves.length=Greensleves_notes_length;
	greendleves.rate=6000;
	
	
}
