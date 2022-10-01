#include "RGB.h"
#include "colors.h"

int const RGB_PINS[3] = {4, 3, 2};

int Colors[5] = {WHITE, RED, BLUE, GREEN, RED};

void setup() {
  // Setting up the RGD LED pins.
  for (int i = 0; i < 3; i++)
  {
    pinMode(RGB_PINS[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 3; i++)
  {
    Flash(RGB_PINS, Colors[i]);
  }
}
