#include <DS3231.h>
DS3231  rtc(SDA, SCL);

int LED = 4; // LED to indicate time

Time t;
int Alarm_hour = 0;
int Alarm_min = 0;

void setup() {
  
  Serial.begin(96000);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  rtc.begin();

  // Set time  and date
  rtc.setDOW(THURSDAY); // Day of the week
  rtc.setTime(18,00,00); // h:m:s 24 hour format
  rtc.setDate(4,1,2021); // M:D:Y date format

  // Set an alarm(a predefined time to light the LED)
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((Alarm_hour == t.hour) && (Alarm_min == t.min){
    digitalWrite(LED,HIGH);
  }
  delay(1);
}
