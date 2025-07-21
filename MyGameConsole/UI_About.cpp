#include "UI_About.h"
#include "Screen_Manager.h"
#include "TFT_Wrapper.h"
#include "UI_Main_Menu.h"
#include "Input.h"

void drawAboutScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("About This Device:", 10, 20);
  tft.setTextSize(1);
  tft.drawString("- Custom ESP32 handheld", 10, 50);
  tft.drawString("- Powered by TFT_eSPI", 10, 70);
  tft.drawString("- Use 'a' to go back", 10, 100);
}

void aboutScreenLoop() {
  if (backPressed) {
    currentScreen = SCREEN_HOME;
    tft.fillScreen(TFT_BLACK);
    drawStaticUI();
    drawAllMenuItems();
  }
}
