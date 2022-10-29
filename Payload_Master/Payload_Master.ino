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

// Set up the sensors
Adafruit_SHT31  sht31 = Adafruit_SHT31();
Adafruit_BMP3XX bmp;

File currentFile;

int const RGB_PINS[3] = {2, 3, 4};

unsigned long previousMillis = 0;

const long interval = 300000;  // interval at which to blink (milliseconds)

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

  if (!sht31.begin(0x44)) {   
    Serial.println("Can't find SHT31!");
    RGB_Light(RGB_PINS, RED);
    while (1);
  }

  // Move this to a different file
  if(!SD.begin(4)){
    Serial.println("Initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
    while(1);
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

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

int currentFileNum = 1;
void loop() {
  unsigned long currentMillis = millis();

  bmp.performReading();
  
  // Serial printing
  Serial.print("BMP Temperature = ");
  Serial.print(bmp.temperature);
  Serial.print("\t");
  Serial.print("BMP Altitude = ");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.print(" *C");

  Serial.print("\t\t");

  Serial.print("SHT31 Temperature = ");
  Serial.print(sht31.readTemperature());
  Serial.print("\t");
  Serial.print("SHT31 Humidity = ");
  Serial.print(sht31.readHumidity());
  Serial.println(" *C");

  // Current file printing
  currentFile.print(currentMillis);
  currentFile.print(",");
  currentFile.print(bmp.temperature);
  currentFile.print(",");
  currentFile.print(bmp.readAltitude(1013.25));
  currentFile.print(",");
  currentFile.println(sht31.readTemperature());
  currentFile.print(",");
  currentFile.print(sht31.readHumidity());


  if (SD.begin(4)) {
    if (currentMillis - previousMillis >= interval) {
      // save the last time we created a file.
      previousMillis = currentMillis;

      currentFile.close();
      Serial.println("data file is closed.");

      currentFile = SD.open("data_" + String(currentFileNum) + ".txt", FILE_WRITE);
      Serial.println("data is open.");

      currentFile.println("time,bmp_tmp,bmp_alt,sht_tmp,sht_hum");
      Serial.println(currentMillis/300000);
    }
  } else {
    Serial.println("Put the SD card in!");
    RGB_Light(RGB_PINS, YELLOW);
  }
  
  RGB_Light(RGB_PINS, GREEN);
  delay(5000);
  RGB_Light(RGB_PINS, GREEN);
}