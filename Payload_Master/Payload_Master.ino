/***************************
*
* The Main code 
*
***************************/

// Move this to a seperate header file.
#include "RGB.h"
#include "colors.h"
#include <SPI.h>
#include <SD.h>


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

#include "Adafruit_SHT31.h"



File data;

int const RGB_PINS[3] = { 2, 3, 4 };

// Set up the sensors
Adafruit_SHT31  sht31 = Adafruit_SHT31();
Adafruit_BMP3XX bmp;

File currentFile;

int const RGB_PINS[3] = { 2, 3, 4 };

unsigned long previousMillis = 0;

int ledState = LOW;

const long interval = 1000;  // interval at which to blink (milliseconds)


void setup() {
  // Setting up Serial
  Serial.begin(115200);

  while (!Serial) {
    ; // Wait for Serial port to connect
  }

  /**************************************************************************************
  * You need to move both the BMP and SHT sensor setup to a differnt cpp file.
  **************************************************************************************/

  if (!bmp.begin_I2C(0x77)) {   // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Can't find BMP388!");
    RGB_Light(RGB_PINS, RED);
    while (1);
  }

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Can't find SHT31!");
    RGB_Light(RGB_PINS, RED);
    while (1);
  }


  // Move this to a differnt file
  if(!SD.begin(4)){
    Serial.println("Initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
    while(1);
  }

  Serial.println("initialization done. (I did what I was supposed to!)");

  currentFile = SD.open("data.txt", FILE_WRITE);


  // if the file opened okay, write to it:

  if (data) {
    Serial.print("Writing to data.txt...");
    data.println("Hey! Listen!");

    // close the file:
    data.close();
    Serial.println("Done writing. ");

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

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

int currentFileNum = 1;
void loop() {
  if (! bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  RGB_Light(RGB_PINS, GREEN);

  Serial.print("BMP Temperature = ");
  Serial.print(bmp.temperature);
  Serial.print(" *C");

  Serial.print("\t\t");

  Serial.print("SHT31 Temperature = ");
  Serial.print(sht31.readTemperature());
  Serial.println(" *C");

  delay(2000);
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