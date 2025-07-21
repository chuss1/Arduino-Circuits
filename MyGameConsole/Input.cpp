#include "Input.h"
#include <Arduino.h>

bool upPressed = false;
bool downPressed = false;
bool selectPressed = false;
bool backPressed = false;

void readInput() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'w': upPressed = true; break;
      case 's': downPressed = true; break;
      case 'd': selectPressed = true; break;
      case 'a': backPressed = true; break;
    }
  }
}

void resetInput() {
  upPressed = false;
  downPressed = false;
  selectPressed = false;
  backPressed = false;
}
