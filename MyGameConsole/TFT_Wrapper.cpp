#include "TFT_Wrapper.h"

TFT_eSPI tft = TFT_eSPI();

void tft_init() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
}

void drawStaticUI() {
  tft.fillRect(0, 0, SCREEN_WIDTH, 50, TFT_DARKGREEN);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("ESP32 Game Console", SCREEN_WIDTH / 2, 25);
}
