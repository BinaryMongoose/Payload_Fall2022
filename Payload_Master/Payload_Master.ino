#include "RGB.h"
#include "colors.h"
#include <SPI.h>
#include <SD.h>

File data;

int const RGB_PINS[3] = { 4, 3, 2 };

int Colors[5] = { WHITE, RED, BLUE, GREEN, RED };

void setup() {
  // Setting up Serial
  Serial.begin(9600);

  while (!Serial) {
    ; // Wait for Serial port to connect
  }

  if(!SD.begin(4)){
    Serial.println("Initialization  failed! Try turning me on and off.");
    while(1);
  }

  Serial.println("initialization done. (I did what I was supposed to!)");

  data = SD.open("data.txt", FILE_WRITE);

    // if the file opened okay, write to it:

  if (data) {
    Serial.print("Writing to data.txt...");
    data.println("testing 1, 2, 3.");

    // close the file:
    data.close();
    Serial.println("Done writing. ");
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening data.txt");
  }

  // Setting up the RGD LED pins.
  for (int i = 0; i < 3; i++) {
    pinMode(RGB_PINS[i], OUTPUT);
  }
}

void loop() {
  Flash(RGB_PINS, WHITE);
}