#include <DS3231.h>
DS3231  rtc(SDA, SCL);

int LED1 = 4; // LED to indicate time
int LED2 = 5;

int Alarm1_hour = 18;
int Alarm1_min = 0;

int Alarm2_hour = 18;
int Alarm2_min = 1;
String t;
int h;
int m;

int count1 = 0;
int count2 = 0;

void setup() {
  
  Serial.begin(115200);
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
  t = rtc.getTimeStr();
  h = t.substring(0,2).toInt();
  m = t.substring(3,5).toInt();
  Serial.println(t);
  Serial.println(h,m);
  if ((Alarm1_hour == h) && (Alarm1_min == m)){
    Serial.println("Alarm 1");
    digitalWrite(LED1,HIGH);
  }
  else if ((Alarm2_hour == h) && (Alarm2_min == m)){
    Serial.println("Alarm 2");
    digitalWrite(LED2,HIGH);
  }
  delay(1000);
}
