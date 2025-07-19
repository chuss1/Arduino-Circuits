#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); // Invoke TFT instance

void setup() {
  Serial.begin(115200);

  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH); // backlight on

  tft.init();
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(100, 10);
  tft.println("Hello, ESP32 with TFT_eSPI!");
}

void loop() {
  // your code here
}
