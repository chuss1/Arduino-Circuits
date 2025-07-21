#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

enum Screen {
  SCREEN_HOME,
  SCREEN_ABOUT
};

Screen currentScreen = SCREEN_HOME;

const char* menuItems[] = { "Start Game", "Settings", "About" };
const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;

int selectedItem = 0;
int lastSelectedItem = -1;

// Simulated button input states (replace with your actual input)
bool upPressed = false;
bool downPressed = false;
bool selectPressed = false;
bool backPressed = false;

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);

  drawStaticUI();
  drawAllMenuItems();
  lastSelectedItem = selectedItem;
}

void loop() {
  // Simulate input (for testing)
  // Use serial input or other triggers in real code
  // For demo: press buttons via serial commands

  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'w': upPressed = true; break;
      case 's': downPressed = true; break;
      case 'd': selectPressed = true; break;
      case 'a': backPressed = true; break;
    }
  }

  switch (currentScreen) {
    case SCREEN_HOME: homeScreenLoop(); break;
    case SCREEN_ABOUT: aboutScreenLoop(); break;
  }

  // Reset inputs
  upPressed = false;
  downPressed = false;
  selectPressed = false;
  backPressed = false;
}

void homeScreenLoop() {
  if (upPressed) {
    int newSelected = (selectedItem - 1 + menuItemCount) % menuItemCount;
    updateMenuSelection(selectedItem, newSelected);
    selectedItem = newSelected;
  }
  if (downPressed) {
    int newSelected = (selectedItem + 1) % menuItemCount;
    updateMenuSelection(selectedItem, newSelected);
    selectedItem = newSelected;
  }
  if (selectPressed) {
    if (selectedItem == 2) {  // About button
      currentScreen = SCREEN_ABOUT;
      drawAboutScreen();
    }
    // else ignore for now
  }
}

void aboutScreenLoop() {
  if (backPressed) {
    currentScreen = SCREEN_HOME;
    tft.fillScreen(TFT_BLACK);
    drawStaticUI();
    drawAllMenuItems();
    lastSelectedItem = selectedItem;
  }
}

void drawStaticUI() {
  tft.fillRect(0, 0, SCREEN_WIDTH, 50, TFT_DARKGREEN);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("ESP32 Game Console", SCREEN_WIDTH / 2, 25);
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
  tft.setTextDatum(MC_DATUM);  // 🔧 Center align text
  tft.drawString(menuItems[index], SCREEN_WIDTH / 2, y + itemHeight / 2);
}

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
