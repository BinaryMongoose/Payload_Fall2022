#include "RGB.h"
#include "colors.h"
#include <SPI.h>
#include <SD.h>

File currentFile;

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

  currentFile = SD.open("data.txt", FILE_WRITE);

  if (currentFile) {
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

int currentFileNum = 1;
void loop() {
  unsigned long currentMillis = millis();

  if (SD.begin(4)) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      currentFile.close();
      Serial.println("data file is closed.");

      currentFile = SD.open("data_" + String(currentFileNum) + ".txt", FILE_WRITE);
      Serial.println("data is open.");

      currentFile.println(currentMillis/1000);
      Serial.println(currentMillis/1000);
      currentFileNum += 1;
    }
  } else {
    Serial.println("Put the SD card in!");
  }

}