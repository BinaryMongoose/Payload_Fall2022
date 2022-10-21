#include "RGB.h"
#include "colors.h"
#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

File data;

int const RGB_PINS[3] = { 2, 3, 4 };

int Colors[5] = { WHITE, RED, BLUE, GREEN, RED };

Adafruit_BMP3XX bmp;

void setup() {
  // Setting up Serial
  Serial.begin(115200);

  while (!Serial) {
    ; // Wait for Serial port to connect
  }

  if (!bmp.begin_I2C(0x77)) {   // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }

  if(!SD.begin(4)){
    Serial.println("Initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
    while(1);
  }

  Serial.println("initialization done. (I did what I was supposed to!)");

  data = SD.open("data.txt", FILE_WRITE);

    // if the file opened okay, write to it:

  if (data) {
    Serial.print("Writing to data.txt...");
    data.println("Hey! Listen!");

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

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  RGB_Light(RGB_PINS, GREEN);

  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");
}