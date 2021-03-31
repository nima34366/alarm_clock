#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,2,3,4,5);
String a;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  while(Serial.available()){
  a= Serial.readString();
  lcd.clear();
  lcd.print(a);
  }

}