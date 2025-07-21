#include "UI_Main_Menu.h"
#include "Screen_Manager.h"
#include "TFT_Wrapper.h"
#include "Input.h"
#include "UI_About.h"

const char* menuItems[] = { "Start Game", "Settings", "About" };
const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

int selectedItem = 0;
int lastSelectedItem = -1;

void homeScreenLoop() {
  if (upPressed) {
    int newSel = (selectedItem - 1 + menuItemCount) % menuItemCount;
    updateMenuSelection(selectedItem, newSel);
    selectedItem = newSel;
  }
  if (downPressed) {
    int newSel = (selectedItem + 1) % menuItemCount;
    updateMenuSelection(selectedItem, newSel);
    selectedItem = newSel;
  }
  if (selectPressed && selectedItem == 2) {
    currentScreen = SCREEN_ABOUT;
    drawAboutScreen();
  }
}

void drawAllMenuItems() {
  for (int i = 0; i < menuItemCount; i++) {
    drawMenuItem(i, i == selectedItem);
  }
}

void updateMenuSelection(int oldSel, int newSel) {
  if (oldSel >= 0) drawMenuItem(oldSel, false);
  drawMenuItem(newSel, true);
}

void drawMenuItem(int index, bool selected) {
  int itemHeight = 50;
  int spacing = 10;
  int y = 70 + index * (itemHeight + spacing);
  int x = 90;
  int width = SCREEN_WIDTH - 2 * x;

  if (selected) {
    tft.fillRoundRect(x, y, width, itemHeight, 10, TFT_GREEN);
    tft.setTextColor(TFT_BLACK, TFT_GREEN);
  } else {
    tft.fillRoundRect(x, y, width, itemHeight, 10, TFT_BLACK);
    tft.drawRoundRect(x, y, width, itemHeight, 10, TFT_DARKGREY);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }

  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(menuItems[index], SCREEN_WIDTH / 2, y + itemHeight / 2);
}
