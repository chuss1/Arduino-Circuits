#include "Screen_Manager.h"
#include "Input.h"
#include "UI_Main_Menu.h"
#include "UI_About.h"
#include "TFT_Wrapper.h"

void setup() {
  Serial.begin(115200);
  tft_init();
  drawStaticUI();
  drawAllMenuItems();
}

void loop() {
  readInput();

  switch (currentScreen) {
    case SCREEN_HOME: homeScreenLoop(); break;
    case SCREEN_ABOUT: aboutScreenLoop(); break;
  }

  resetInput();
}
