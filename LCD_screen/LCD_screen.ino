// This script will display two pieces of text with flowing characters

#include <LiquidCrystal.h>

char array1[] = " Cr0nus LCD               ";
char array2[] = " Hello, World!            ";
int time = 750;

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
// 4  = Register Select
// 6  = Enable Pin
// 10 = Data Pin 4
// 11 = Data Pin 5
// 12 = Data Pin 6
// 13 = Data Pin 7

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(15, 0);
  for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++) {
    lcd.scrollDisplayLeft();
    lcd.print(array1[positionCounter1]);
    delay(time);
  }

  lcd.clear();

  lcd.setCursor(15, 1);
  for (int positionCounter2 = 0; positionCounter2 < 26; positionCounter2++) {
    lcd.scrollDisplayLeft();
    lcd.print(array2[positionCounter2]);
    delay(time);
  }

  lcd.clear();
}
