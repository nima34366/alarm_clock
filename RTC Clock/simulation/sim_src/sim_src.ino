#include <DS3231.h>
DS3231  rtc(SDA, SCL);

int LED1 = 4; // LED to indicate time
int LED2 = 5;

Time t;
int Alarm1_hour = 18;
int Alarm1_min = 0;

int Alarm2_hour = 18;
int Alarm2_min = 1;

void setup() {
  
  Serial.begin(96000);
  rtc.begin();
  
  pinMode(LED1,OUTPUT);
  digitalWrite(LED1,LOW);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED2,LOW);

  // Set time  and date
  rtc.setDOW(THURSDAY); // Day of the week
  rtc.setTime(18,00,00); // h:m:s 24 hour format
  rtc.setDate(4,1,2021); // M:D:Y date format

  // Set an alarm(a predefined time to light the LED)
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((Alarm1_hour == t.hour) && (Alarm1_min == t.min)){
    digitalWrite(LED1,HIGH);
  }
  else if ((Alarm2_hour == t.hour) && (Alarm2_min == t.min)){
    digitalWrite(LED2,HIGH);
  }
  delay(1);
}
