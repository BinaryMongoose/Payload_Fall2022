/***************************
 The Main code 

 About 60 readings per file
***************************/

#include "Payload_Master.h"

// Set up the sensors
Adafruit_SHT31  sht31 = Adafruit_SHT31();
Adafruit_BMP3XX bmp;

File currentFile;

int const RGB_PINS[3] = {2, 3, 4};

unsigned long previousMillis = 0;

const int SECOND       = 1000;
const int FIVE_SECONDS = SECOND * 5;
const int MINUTE       = SECOND * 60; 
const int FIVE_MINUTES = MINUTE * 5;


const int fileInterval = MINUTE;  // fileInterval at which to create a new file
int currentFileNum = FIVE_MINUTES;

void setup() {
  // Setting up Serial
  Serial.begin(115200);

  /**************************************************************************************
  * You need to move both the BMP and SHT sensor setup to a differnt cpp file.
  **************************************************************************************/

  if (!bmp.begin_I2C(0x77)) {
    Serial.println(F("Can't find BMP388!"));
    RGB_Light(RGB_PINS, YELLOW);
    while (1);
  }

  if (!sht31.begin(0x44)) {   
    Serial.println(F("Can't find SHT31!"));
    RGB_Light(RGB_PINS, YELLOW);
    while (1);
  }

  // Move this to a different file
  if(!SD.begin(4)){
    Serial.println("SD initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
    while(1);
  }

  Serial.println("SD initialization done. (I did what I was supposed to!)");

  currentFile = SD.open("data_0.csv", FILE_WRITE);

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

  play();
}

void loop() {
  unsigned long currentMillis = millis();
  if(!bmp.performReading()){
    RGB_Light(RGB_PINS, RED);
  }
  
  //Log_Serial(currentMillis);
  Log_SD(currentMillis);

    if (currentMillis - previousMillis >= fileInterval) {
      Create_File(currentMillis);
    }

  RGB_Light(RGB_PINS, GREEN);
  delay(FIVE_SECONDS); 
  RGB_Light(RGB_PINS, GREEN);
}

void Log_Serial(long currentMillis){
  // Serial printing
  //Serial.print(currentMillis/1000);
  Serial.print(F(","));
  Serial.print(bmp.temperature);
  Serial.print(F(","));
  Serial.print(bmp.readAltitude(1013.25));
  Serial.print(F(","));
  Serial.print(sht31.readTemperature());
  Serial.print(F(","));
  Serial.println(sht31.readHumidity());
}

void Log_SD(long currentMillis){
    // Current file printing
  currentFile.print(currentMillis/1000);
  currentFile.print(",");
  currentFile.print(bmp.temperature);
  currentFile.print(",");
  currentFile.print(bmp.readAltitude(1013.25));
  currentFile.print(",");
  currentFile.print(sht31.readTemperature());
  currentFile.print(",");
  currentFile.println(sht31.readHumidity());
}

void Create_File(long currentMillis){
    // save the last time we created a file.
    previousMillis = currentMillis;
    currentFile.close();
    currentFile = SD.open("data_" + String(currentFileNum) + ".csv", FILE_WRITE);
    currentFile.println("time,bmp_tmp,bmp_alt,sht_tmp,sht_hum");
    currentFileNum += 1; // THis is important! Increments the file number.
}
