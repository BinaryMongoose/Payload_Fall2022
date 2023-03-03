/*
 The Main code 

 About 60 readings per file

 BTW: The boxes name is Jerry.
*/

/*
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
CHANGE THE BUZZER PIN NUMBER
*/
#include "Payload_Master.h"

// Set up the sensors
Adafruit_SHT31  sht31 = Adafruit_SHT31();
Adafruit_BMP3XX bmp;

File currentFile;

int const RGB_PINS[3] = {2, 3, 4};

unsigned long previousMillis = 0;

const int ONE_SECOND   = 1000;
const int FIVE_SECONDS = ONE_SECOND * 5;
const int ONE_MINUTE       = ONE_SECOND * 60; 
const int FIVE_MINUTES = ONE_MINUTE * 5;

<<<<<<< HEAD
int fileInterval;
int currentFileNum = 0;

bool DEBUG = true;
=======
const long SECOND       = 1000;
const long FIVE_SECONDS = SECOND*5;
const long TEN_SECONDS  = SECOND*10;
const long MINUTE       = SECOND*6; 
const long FIVE_MINUTES = MINUTE*5;


const long fileInterval = TEN_SECONDS;  // fileInterval at which to create a new file
>>>>>>> parent of 461f85c (Finished bare bones.)

void setup() {
  // Setting up Serial
  Serial.begin(115200);

<<<<<<< HEAD
  // Setting up the BMP388
=======
  while (!Serial) {
    ; // Wait for Serial port to connect
  }

  Serial.println("**********************");
  Serial.println();

  /**************************************************************************************
  * You need to move both the BMP and SHT sensor setup to a differnt cpp file.
  **************************************************************************************/

>>>>>>> parent of 461f85c (Finished bare bones.)
  if (!bmp.begin_I2C(0x77)) {
    Serial.println(F("Can't find BMP388!"));
    RGB_Light(RGB_PINS, YELLOW);
    while (1);
  }

  // Setting up the SHT32
  if (!sht31.begin(0x44)) {   
    Serial.println(F("Can't find SHT31!"));
    RGB_Light(RGB_PINS, YELLOW);
    while (1);
  }

  // Making sure the SD card is working.
  if(!SD.begin(4)){
    Serial.println("SD initialization  failed! Try turning me on and off.");
    RGB_Light(RGB_PINS, RED);
    while(1);
  }

  Serial.println("initialization done. (I did what I was supposed to!)");

<<<<<<< HEAD
  currentFile = SD.open("data_0.csv", FILE_WRITE); // The first file has been born.
=======
  currentFile = SD.open("data_0.txt", FILE_WRITE);
>>>>>>> parent of 461f85c (Finished bare bones.)

  // Set up the RGD LED pins.
  for (int i = 0; i < 3; i++) {
    pinMode(RGB_PINS[i], OUTPUT);
  }

  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  // If we are NOT debugging, set the file interval rate to 5 min. 
  if (!DEBUG){
    fileInterval = FIVE_MINUTES;  // fileInterval at which to create a new file
  } else {
    fileInterval = ONE_MINUTE;
  }

  // Jerry lets us know he's never gonna give us up.
  play();
}

int currentFileNum = 1;
void loop() {
  /* Runs over and over again. Hence the name Loop. */
  unsigned long currentMillis = millis(); // 
  if(!bmp.performReading()){
    RGB_Light(RGB_PINS, RED);
  }
  
<<<<<<< HEAD
  // If we are debugging log the serial. 
  if (DEBUG == true){
    Log_Serial(currentMillis);
  }
  
  // rite to the current file.
  Log_SD(currentMillis);

  // If it's been 5 min, make a new file.
  if (currentMillis - previousMillis >= fileInterval) {
    Create_File(currentMillis);
  }


  // Status indicator
  RGB_Light(RGB_PINS, GREEN);

  // If we are not Debugging set the sampling rate to 5 seconds.
  if (!DEBUG){
    delay(FIVE_SECONDS);
  } else {
    delay(ONE_SECOND);
  }

  // Status indicator
  RGB_Light(RGB_PINS, GREEN);
=======
  Log_Serial(currentMillis);

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


  if (SD.begin(4)) {
    if (currentMillis - previousMillis >= fileInterval) {
      // save the last time we created a file.
      previousMillis = currentMillis;

      currentFile.close();
      Serial.println("data file is closed.");

      currentFile = SD.open("data_" + String(currentFileNum) + ".txt", FILE_WRITE);
      Serial.println("data is open.");

      currentFile.println("time,bmp_tmp,bmp_alt,sht_tmp,sht_hum");

      currentFileNum += 1; // THis is important! Increments the file number.
    }
  } else {
    Serial.println("Put the SD card in!");
    RGB_Light(RGB_PINS, ORANGE);
  }
  
  RGB_Light(RGB_PINS, GREEN);
  delay(FIVE_SECONDS);
  RGB_Light(RGB_PINS, GREEN);
>>>>>>> parent of 461f85c (Finished bare bones.)
}

void Log_Serial(long currentMillis){
  /** Serial Printing. **/
  Serial.print(F(","));
  Serial.print(bmp.temperature);            // Inside Temperature
  Serial.print(F(","));
  Serial.print(bmp.readAltitude(1013.25));  // Alt
  Serial.print(F(","));
  Serial.print(sht31.readTemperature());    // Outside Temperature
  Serial.print(F(","));
  Serial.println(sht31.readHumidity());     // Outside Humidity
}
<<<<<<< HEAD

void Log_SD(long currentMillis){
  /** Logging the current file. **/
  currentFile.print(currentMillis/1000);        // Convert milliseconds to seconds
  currentFile.print(",");
  currentFile.print(bmp.temperature);           // Inside Temperature
  currentFile.print(",");
  currentFile.print(bmp.readAltitude(1013.25)); // Alt
  currentFile.print(",");
  currentFile.print(sht31.readTemperature());   // Outside Temperature
  currentFile.print(",");
  currentFile.println(sht31.readHumidity());    // Outside Humdidty
}

void Create_File(long currentMillis){
  /* Every time this code is run it creates 
     a new file with the name DATA_x.
     x is the current file number + 1. */

  previousMillis = currentMillis; // Save last time we created a file. 
  currentFile.close(); // Close current file
  currentFile = SD.open("data_" + String(currentFileNum) + ".csv", FILE_WRITE); // Create a new file
  currentFile.println("time,bmp_tmp,bmp_alt,sht_tmp,sht_hum"); // Create CSV header
  currentFileNum += 1; // Increment the file number.
}
=======
>>>>>>> parent of 461f85c (Finished bare bones.)
