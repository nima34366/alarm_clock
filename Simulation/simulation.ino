#include <Keypad.h>

const int ROW_NUM = 3; //four rows
const int COLUMN_NUM = 3; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};

byte pin_rows[ROW_NUM] = {A0, A1, A2}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {A3, A4, A5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup()
{
 for (int i=1; i<=9; i++) 
 {
   pinMode(i, OUTPUT);
 }
}

void loop()
{
  int key = keypad.getKey();
  
 for (int i=1; i<=9; i++)
 {
     if (key !=0 )
     {
       for (int k = 1; k<=key; k++)
        {
        digitalWrite(k,HIGH) ;
        }
     } 
     else
     {
       for (int p = 1; p<=9; p++)
       {        
        digitalWrite(p,LOW);
       }
     }
 }
}
