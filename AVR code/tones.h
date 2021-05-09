
 
#include "notes.h"

/*greendleaves*/

int Greendleves_notes[]={NOTE_G4,NOTE_AS4,NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4,
	NOTE_A4, NOTE_FS4, NOTE_D4, NOTE_G4,NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_DS5, NOTE_D5,NOTE_C5, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_A4,
	NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_G4,NOTE_F5, NOTE_E5, NOTE_D5,NOTE_C5, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4,NOTE_AS4, NOTE_G4, NOTE_G4,
	NOTE_FS4, NOTE_G4,NOTE_A4, NOTE_FS4, NOTE_D4,NOTE_F5, NOTE_E5, NOTE_D5,NOTE_C5, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4,NOTE_AS4, NOTE_A4, NOTE_G4,
NOTE_FS4, NOTE_E4, NOTE_FS4,NOTE_G4};


int Greendleves_notes_durations[]={8,4,8,-8,16,8,4,8,-8,16,8,4,8,-8,16,8,4,8,4,8,4,8,-8,16,8,
	4,8,-8,16,8,-8,16,8,-8,16,8,4,8,-8,16,8,-8,16,8,-8,16,8,-2,
2,16,8,4,8,-8,16,8,4,8,-8,16,8,4,8,04,2,16,8,4,8,-8,16,8};
int Greensleves_notes_length = sizeof(Greendleves_notes) / sizeof(Greendleves_notes[0]) ;

/*star wars*/

int starwars_notes[]={NOTE_AS4,NOTE_AS4, NOTE_AS4,NOTE_F5, NOTE_C6,NOTE_AS5, NOTE_A5,NOTE_G5, NOTE_F6, NOTE_C6,NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
	NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,NOTE_F5, NOTE_C6,NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
	NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,NOTE_D5,NOTE_D5, NOTE_AS5,
	NOTE_A5, NOTE_G5, NOTE_F5,NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5,NOTE_C5, NOTE_C5,NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5,
	NOTE_G5, NOTE_F5,NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,NOTE_D5,NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,NOTE_F5, NOTE_G5, NOTE_A5,
NOTE_G5, NOTE_D5, NOTE_E5,NOTE_C6, NOTE_C6,NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,NOTE_C6};

int starwars_notes_durations[]={8,8,8,2,2,8,8,8,2,4,8,8,8,2,4,8,8,8,2,8,8,8,2,2,8,8,8,2,4,8,8,
	8,2,4,8,8,8,2,-8,16,-4,8,8,8,8,8,8,8,8,4,8,4,-8,16,-4,8,8,8,8,
8,-8,16,2,8,8,-4,8,8,8,8,8,8,8,8,4,8,4,-8,16,4,8,4,8,4,8,4,8,1};
int starwars_notes_length = sizeof(starwars_notes) / sizeof(starwars_notes[0]) ;

/*game of throns*/

int game_of_throns_notes[]={NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4,
	NOTE_DS4, NOTE_F4,NOTE_G4, NOTE_C4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4, NOTE_E4,NOTE_F4,NOTE_G4,
	NOTE_C4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4, NOTE_F4,NOTE_G4,NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,
	NOTE_D4, NOTE_F4, NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_C4,NOTE_G4, NOTE_C4,NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_C4, NOTE_DS4, NOTE_F4,
	NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_DS4,NOTE_D4, NOTE_C4,NOTE_G4,NOTE_C4,NOTE_DS4, NOTE_F4,NOTE_G4,
	NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_D4,NOTE_F4,NOTE_AS3,NOTE_D4,NOTE_DS4,NOTE_D4,NOTE_AS3,NOTE_C4,NOTE_C5,NOTE_AS4,NOTE_C4,NOTE_G4,
	NOTE_DS4,NOTE_DS4,NOTE_F4,NOTE_G4,NOTE_C5,NOTE_AS4,NOTE_C4,NOTE_G4,NOTE_DS4,NOTE_DS4, NOTE_D4,NOTE_C5,NOTE_G4,NOTE_GS4,NOTE_AS4,
	NOTE_C5, NOTE_G4, NOTE_GS4, NOTE_AS4,NOTE_C5, NOTE_G4, NOTE_GS4,NOTE_AS4,NOTE_C5, NOTE_G4,NOTE_GS4,NOTE_AS4,REST,NOTE_GS5,
NOTE_AS5, NOTE_C6, NOTE_G5,NOTE_GS5,NOTE_AS5,NOTE_C6,NOTE_G5, NOTE_GS5,NOTE_AS5,NOTE_C6,NOTE_G5,NOTE_GS5,NOTE_AS5 };


int game_of_throns_notes_durations[]={8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,
	-4,-4,16,16,4,4,16,16,-1,-4,-4,16,16,4,-4,16,16,-1,-4,-4,16,16,4,4,16,16,-1,-4,
	-4,16,16,4,-4,16,16,-1,-4,-4,16,16,4,4,16,16,-2,-4,-4,-8,-8,-8,-8,-1,-2,-2,-2,
	-2,-2,-4,-4,-1,-2,-2,-2,-2,-2,-4,-4,8,8,16,16,8,8,16,16,8,8,16,16,8,8,16,16,4,16,
16,8,8,16,16,8,16,16,16,8,8,16,16};
int game_of_throns_notes_length = sizeof(game_of_throns_notes) / sizeof(game_of_throns_notes[0]) ;
/*harry potter*/

int harry_potter_notes[]={  REST, NOTE_D4,NOTE_G4, NOTE_AS4, NOTE_A4,NOTE_G4, NOTE_D5,NOTE_C5,NOTE_A4,NOTE_G4, NOTE_AS4,NOTE_A4,NOTE_F4,NOTE_GS4,NOTE_D4,
	NOTE_D4,NOTE_G4,NOTE_AS4,NOTE_A4,NOTE_G4,NOTE_D5,NOTE_F5,NOTE_E5,NOTE_DS5,NOTE_B4,NOTE_DS5,NOTE_D5,NOTE_CS5,NOTE_CS4,NOTE_B4,NOTE_G4,
	NOTE_AS4,NOTE_D5,NOTE_AS4,NOTE_D5,NOTE_AS4,NOTE_DS5,NOTE_D5,NOTE_CS5,NOTE_A4,NOTE_AS4,NOTE_D5,NOTE_CS5,NOTE_CS4,NOTE_D4,NOTE_D5,REST,
NOTE_AS4,NOTE_D5,NOTE_AS4,NOTE_D5,NOTE_AS4,NOTE_F5,NOTE_E5,NOTE_DS5,NOTE_B4,NOTE_DS5, NOTE_D5, NOTE_CS5,NOTE_CS4,NOTE_AS4,NOTE_G4};


int harry_potter_notes_durations[]={2,4,-4,8,4,2,4,-2,-2,-4,8,4,2,4,-1,4,-4,8,4,2,4,2,4,2,4,-4,8,4,2,4,-1,4,2,
4,2,4,2,4,2,4,-4,8,4,2,4,-1,4,4,2,4,2,4,2,4,2,4,-4,8,4,2,4,-1};
int harry_potter_notes_length = sizeof(harry_potter_notes) / sizeof(harry_potter_notes[0]) ;
