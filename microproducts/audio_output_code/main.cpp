
#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "notes.h"
#include "tones.h"
#define PORT PORTC
#define PIN_OUT PINC0
#define PIN_IN PINC2
int tone_number=0;
bool debounce1=true;

class Tones{
	public:
	int *notes;
	int *durations;
	int length;
	int rate;
	void PLAYTONE(float Note_frequency, float Note_duration){
		
		long cycles;
		float complete_period;
		DDRC |= (1 << PIN_OUT);
		
		if (Note_frequency==0){
			
			PORT &= ~(1 << PIN_OUT);
			_delay_us(Note_duration);
		}
		else{			
			complete_period=(1/Note_frequency)*1000;
			cycles=Note_duration/(complete_period*2);
			for (int i=0;i<cycles;i++){
				_delay_ms(complete_period/2);
				PORT |= (1 << PIN_OUT);
				_delay_ms(complete_period/2);
				PORT &= ~(1 << PIN_OUT);				
			}
		}
	}
	void play(){
	
		while ((PINC & (1<< PIN_IN))==0){
			for (int i = 0; i <length ; i = i + 1){
			if((PINC & (1<< PIN_IN)) != 0){
				debounce1=true;
				break;
			}				
			PLAYTONE(notes[i],(rate/abs(durations[i])));}			
		}
	}
};	
	
int main(void)
{		
	DDRC &= ~(1 << PIN_IN);
	PORT |= 1 << PIN_IN;
	
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
	
    while (1) 
    {
		if ((PINC & (1<< PIN_IN))==0 && debounce1 == true){
			tone_number++;
			if (tone_number==5)
			{tone_number=1;}
			 if (tone_number ==1)
				{harry_potter.play();}
			 if (tone_number ==2)
			 {game_of_throns.play();} 

			 if (tone_number ==3)
			 {starwars.play();} 

			 if (tone_number ==4)
			 {greendleves.play();}	
			
		}		
    }
}
