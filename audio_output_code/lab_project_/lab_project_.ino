
#include "notes.h"
#include "tones.h"

// change this to make the song slower or faster
int speed_adjust = 100;
int button_state = 0;
int length_notes_=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8,INPUT); 
  
}

void playTone(int length_notes, int playing_melody[],int pin){
  int complete_duration = (60000 * 4)/ speed_adjust; // complete duration of the tone
  int given_note_time = 0, duration = 0;
  for (int Note = 0; Note < length_notes * 2; Note = Note + 2){
    given_note_time= playing_melody[Note+1];
    if (given_note_time >0){
      duration=complete_duration/given_note_time;
    } else if (given_note_time <0){
      duration=complete_duration/abs(given_note_time);
      duration *= 1.5;
      
    }
    
    tone(11, playing_melody[Note], duration * 0.9);
    delay(duration);
    noTone(11);
    if (digitalRead(pin)==(LOW)){
      break;
      
    }
  }
      
  }

void loop(){// play a selected tone 
  //int duration = (60000 * 4) / speed_adjust; // complete duration of the tone
  if (digitalRead(6)==  HIGH)// reading the 6 th pin value
  {
    while ((digitalRead(6)==HIGH) == 1)
    {
      length_notes_=Greensleves_notes;
      //int playing_melody_[]=Greensleves;
      int pin1=6;
      
      playTone(Greensleves_notes,Greensleves,pin1);
    }
  }
    
      
  
  else if (digitalRead(7)==HIGH)// reading the 7 th pin value
  {
    while ((digitalRead(7)==HIGH)==1){
      //length_notes_=harry_potter_notes;
      //playing_melody_= harry_potter_melody;
      int pin2=7;
      playTone(harry_potter_notes,harry_potter_melody,pin2);
    }
  }
  else if (digitalRead(8)==HIGH)// reading the 8 th pin value
  {
    while ((digitalRead(8)==HIGH) == 1){
      //length_notes_=game_of_throns_notes;
      //playing_melody_=game_of_throns_melody;
      int pin3=8;
      playTone(game_of_throns_notes,game_of_throns_melody,pin3);
    }
  }
  else if (digitalRead(5)==HIGH)// reading the 8 th pin value
  {
    while ((digitalRead(5)==HIGH) == 1){
      //length_notes_=Star_Wars_theme;
      //playing_melody_=Star_Wars_theme_melody;
      int pin4=5;
      playTone(Star_Wars_theme_notes,Star_Wars_theme_melody,pin4);
    }
  }
  else 
  {
    noTone(11);
  }
      
   
}
