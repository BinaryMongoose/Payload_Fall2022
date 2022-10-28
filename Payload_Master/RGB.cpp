/***********************************************
* Functions for RGB LED
*
* Flash is out of date, needs to be upgraded. 
***********************************************/

#include "RGB.h"

int d = 200;

int CLEAR[3] = {0, 0, 0};

// Flashes the LED.
void Flash(int RGB_PINS[], int RGB_COLOR[]){
  RGB_Light(RGB_PINS, RGB_COLOR);
  delay(d);
  RGB_Light(RGB_PINS, CLEAR);
  delay(d);
}

// Sets the LED to a specific color.
void RGB_Light(int RGB_PINS[], int RGB_COLOR[])
 {
  for (int i = 0; i < 3; i++)
  {
    analogWrite(RGB_PINS[i], RGB_COLOR[i]);
  }
}