#pragma once
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 320;

void tft_init();
void drawStaticUI();
