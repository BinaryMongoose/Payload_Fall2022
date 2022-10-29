/************************************
 RGB header file
 
 To be completely honest, I have no
 idea how this works.
************************************/

#ifndef RGB
#define RGB

#include <Arduino.h>

void Flash(int RGB_PINS[], int RGB_COLOR[]);
void RGB_Light(int RGB_PINS[], int RGB_COLOR[]);

#endif