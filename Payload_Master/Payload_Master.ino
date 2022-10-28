#include "RGB.h"
#include "colors.h"
#include <SPI.h>
#include <SD.h>

File data;

int const RGB_PINS[3] = { 2, 3, 4 };

unsigned long previousMillis = 0;

int ledState = LOW;

const long interval = 1000;  // interval at which to blink (milliseconds)

void setup() {
  // Setting up Serial
  Serial.begin(9600);

  while (!Serial) {
    ; // Wait for Serial port to connect
  }

  if(!SD.begin(4)){
    Serial.println("Initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
  }

  Serial.println("initialization done. (I did what I was supposed to!)");

  data = SD.open("data.txt", FILE_WRITE);

    // if the file opened okay, write to it:

  if (data) {
    Serial.println("Data is open.");
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
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    data.close();
    Serial.println("data file is colsed.");

    data = SD.open("data.txt", FILE_WRITE);
    Serial.println("data is open.");

    data.println(currentMillis/1000);
  }


}