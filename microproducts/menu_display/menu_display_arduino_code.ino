#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,2,3,4,5);
String a;
void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
	

}