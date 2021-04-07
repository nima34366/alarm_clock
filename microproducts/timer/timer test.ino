int led = 13;  // LED connected to digital pin 13
int ten = 7;    // pushbutton connected to digital pin 7
int twenty = 6;    // pushbutton connected to digital pin 6
int thirty = 5;    // pushbutton connected to digital pin 5
int reset = 4;    // pushbutton connected to digital pin 4
int val = 0;      // variable to store the

void setup() {
  // put your setup code here, to run once:
  
pinMode(led, OUTPUT);  // sets the digital pin 13 as output
pinMode(ten, INPUT);    // sets the digital pin 7 as input
pinMode(twenty, INPUT);    // sets the digital pin 6 as input
pinMode(thirty, INPUT);    // sets the digital pin 5 as input
pinMode(reset, INPUT);    // sets the digital pin 4 as input
digitalWrite(led, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  
if (digitalRead(ten)==HIGH)
{val=10;}
if (digitalRead(twenty)==HIGH)
{val=20;}
if (digitalRead(thirty)==HIGH)
{val=30;}
if (digitalRead(reset)==HIGH)
{val=0;
digitalWrite(led,LOW);} 

if(val!=0){
  for (int i = val; i > 0; --i){
    delay(1000);
    }
  digitalWrite(led,HIGH);
  
}
val=0;
}
