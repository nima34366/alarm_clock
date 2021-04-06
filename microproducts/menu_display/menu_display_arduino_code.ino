#include <LiquidCrystal.h>
//setting pins
LiquidCrystal lcd(12,11,2,3,4,5);
int b1=8;
int b2=9;
int b3=10;

//setting variables
int p1val=0;
int n1val=0;
int p2val=0;
int n2val=0;
int p3val=0;
int n3val=0;
int n=0;


void setup() {
  lcd.begin(16, 2);
  lcd.print(n);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
}

void loop() {
  //setting n to increase when there is a change in b1 from low to high
  n1val=digitalRead(b1);
  if ((n1val==HIGH) && (p1val==LOW)){
    n=n+1;
    lcd.clear();
    lcd.print(n);
  }
  p1val=n1val;
  
  //setting n to decrease when there is a change in b2 from low to high
  n2val=digitalRead(b2);
  if ((n2val==HIGH) && (p2val==LOW)){
    n=n-1;
    lcd.clear();
    lcd.print(n);
  }
  p2val=n2val; 
  
  //setting n to 0 when there is a change in b3 from low to high
  n3val=digitalRead(b3);
  if ((n3val==HIGH) && (p3val==LOW)){
    n=0;
    lcd.clear();
    lcd.print(n);
  }
  p3val=n3val; 

}