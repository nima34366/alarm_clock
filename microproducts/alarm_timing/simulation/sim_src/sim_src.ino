#include <DS3231.h>
DS3231  rtc(SDA, SCL);

// Defining indicative LEDs
int alarmActiveLED = A0;
int alarm1Ring = A1; 
int setAlarmLED = A2;
int hrLED = 3;
int minLED = 4;
int setClockLED = A3;

// input bits pins
int d1 = 5;
int d2 = 6;
int d3 = 7;
int d4 = 8;
int d5 = 9;
int d6 = 10;

// Mode switches
int setAlarm = 11;
int setClk = 12;
int snooze = 13;

int Alarm1_hour;
int Alarm1_min;

// switch state variables
int alarmActive = 0;
int alarmSnooze = 0;
int sa;
int sc;

// current time variables
String t;
int h;
int m;

void setup() {
  
  Serial.begin(115200);
  rtc.begin();
  
  pinMode(alarmActiveLED,OUTPUT);
  digitalWrite(alarmActiveLED,LOW);
  pinMode(alarm1Ring,OUTPUT);
  digitalWrite(alarm1Ring,LOW);
  pinMode(setAlarmLED,OUTPUT);
  digitalWrite(setAlarmLED,LOW);
  pinMode(hrLED,OUTPUT);
  digitalWrite(hrLED,LOW);
  pinMode(minLED,OUTPUT);
  digitalWrite(minLED,LOW);
  pinMode(setClockLED,OUTPUT);
  digitalWrite(setClockLED,LOW);

  pinMode(d1,INPUT);
  pinMode(d2,INPUT);
  pinMode(d3,INPUT);
  pinMode(d4,INPUT);
  pinMode(d5,INPUT);
  pinMode(d6,INPUT);

  pinMode(setAlarm,INPUT);
  pinMode(setClk,INPUT);
  pinMode(snooze,INPUT);

  // set date manually 
  rtc.setDate(4,1,2021); // M:D:Y date format
}

void loop() {
  // Get current time
  t = rtc.getTimeStr();
  h = t.substring(0,2).toInt();
  m = t.substring(3,5).toInt();
  Serial.println(t);

  // if set clock button is pressed, set the time
  sc = digitalRead(setClk); // state of set clock
  if (sc == HIGH){
    Serial.println("Setting the clock");
    digitalWrite(setClockLED,HIGH);
    set_time();
    digitalWrite(setClockLED,LOW);
    delay(1000);
  }

  // if set alarm button is pressed without current alarms
  sa = digitalRead(setAlarm); // state of set alarm switch
  if (sa == HIGH && alarmActive == 0){
    // set new alarm
    Serial.println("Setting the alarm");
    digitalWrite(setAlarmLED,HIGH);
    set_alarm();
    digitalWrite(setAlarmLED,LOW);
    
    alarmActive = 1;
    digitalWrite(alarmActiveLED,HIGH);
    delay(1000);
  }
  // if set alarm button is pressed with a current alarm
  sa = digitalRead(setAlarm); // state of set alarm switch
  if (sa == HIGH && alarmActive == 1){
    // delete the current alarm
    Serial.println("Deleting Alarm");
    alarmActive = 0;
    digitalWrite(alarmActiveLED,LOW);
    delay(1000);
  }
  // reaching the active alarm time
  if (Alarm1_hour == h && Alarm1_min == m && alarmActive == 1){
    digitalWrite(alarm1Ring,HIGH);
    Serial.println("Alarm on");
    // ringing until the snooze button is pressed
    while (1){
      int snz = digitalRead(snooze); // state of snooze button
      if (snz == HIGH){
        digitalWrite(alarm1Ring,LOW);
        break;
      }
      delay(100);
    }
    Serial.println("Alarm off");
    alarmActive = 0;
    digitalWrite(alarmActiveLED,LOW);
  }
  delay(100);
}

// Function to read input as integer
int read_digit(){
  int n1 = digitalRead(d1);
  int n2 = digitalRead(d2);
  int n3 = digitalRead(d3);
  int n4 = digitalRead(d4);
  int n5 = digitalRead(d5);
  int n6 = digitalRead(d6);

  int number = 32*n1+16*n2+8*n3+4*n4+2*n5+1*n6;
  return number;
}

// Function to set time
void set_time(){
  int time_h;
  int time_m;
  delay(1000);
  
  // Get hours
  digitalWrite(hrLED,HIGH);
  Serial.println("Enter hours <=24");
  while (1){
    int buttonState = digitalRead(setClk);
    if (buttonState == HIGH){
      time_h = read_digit();
      break;
    delay(100);
    }
  }
  digitalWrite(hrLED,LOW);
  delay(1000);
  
  // Get minutes
  Serial.println("Enter minutes <=60");
  digitalWrite(minLED,HIGH);
  
  while (1){
    int buttonState = digitalRead(setClk);
    if (buttonState == HIGH){
      Serial.println("Read minutes");
      time_m = read_digit();
      break;
    delay(100);
    }
  }
  digitalWrite(minLED,LOW);

  Serial.print("Time Set at ");
  Serial.print(time_h);
  Serial.print(":");
  Serial.println(time_m);
  // Set time
  rtc.setTime(time_h,time_m,00); // h:m:s 24 hour format
}

// Function to set an alarm
void set_alarm(){
  int alarm_h;
  int alarm_m;
  delay(1000);
  
  // Get hours
  Serial.println("Enter hours <=24");
  digitalWrite(hrLED,HIGH);
  while (1){
    int buttonState = digitalRead(setAlarm);
    if (buttonState == HIGH){
      Serial.println("Read hours");
      alarm_h = read_digit();
      break;
    delay(100);
    }
  }
  digitalWrite(hrLED,LOW);
  delay(1000);

  // Get minutes
  Serial.println("Enter minutes <=60");
  digitalWrite(minLED,HIGH);
  
  while (1){
    int buttonState = digitalRead(setAlarm);
    if (buttonState == HIGH){
      Serial.println("Read minutes");
      alarm_m = read_digit();
      break;
    delay(100);
    }
  }
  digitalWrite(minLED,LOW);

  // Set alarm
  Alarm1_hour = alarm_h;
  Alarm1_min = alarm_m;

  Serial.print("Alarm Set at ");
  Serial.print(Alarm1_hour);
  Serial.print(":");
  Serial.println(Alarm1_min);
}
