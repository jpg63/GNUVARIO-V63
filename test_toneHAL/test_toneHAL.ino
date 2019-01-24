#include "toneHAL.h"
#if defined(ESP8266) 
#elif defined(ESP32)
#elif defined(ARDUINO_AVR_PRO)
#include "toneHAL_PRO.h"
#elif defined(ARDUINO_ARCH_SAMD)
#include "toneHAL_M0.h"
#endif

#include <VarioSettings.h>
#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"
SdFat SD;

File myFile;

ToneHAL toneHAL;

const char *filename = "music.wav";

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRateWav = 22050;

void setup() {
  // put your setup code here, to run once:
  SerialPort.begin(115200);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  SerialPort.print("Initializing SD card...");

  if (!SD.begin(SDCARD_CS_PIN)) {
    SerialPort.println("initialization failed!");
//    return;
  }
  else {
    SerialPort.println("initialization done.");

/*    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
       
    }*/
  }
  
  toneHAL.init();
  
  SerialPort.println("Tone Sin");
  for(int i=1; i<100; i++) {
    toneHAL.tone(100*i,10);
    delay(100);
  }
  toneHAL.noTone();
  delay(2000);
  
 /* SerialPort.println("Tone Sin 1000, 50");
  toneHAL.tone(1000,50);
  delay(15000);
  toneHAL.noTone();
  delay(2000); */

#if defined(TONEDAC)
  
  SerialPort.println("Tone Square");
  toneHAL.setWaveForm(WAVEFORM_SQUARE);
  for(int i=1; i<100; i++) {
    toneHAL.tone(100*i,10);
    delay(100);
  }
  toneHAL.noTone();
  delay(2000);
   
  SerialPort.println("Tone Triangle");
  toneHAL.setWaveForm(WAVEFORM_TRIANGLE);
  for(int i=1; i<100; i++) {
    toneHAL.tone(100*i,10);
    delay(100);
  }
  toneHAL.noTone();
  delay(2000); 

  toneHAL.beginPlayWav(sampleRateWav);
//  toneHAL.playWav(filename);
  SerialPort.println("Playing file.....");
#endif //TONEDAC
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  if (SerialPort.available()) {
    char c = SerialPort.read();
    if (c = 'p') {
#if defined(TONEDAC)
      toneHAL.playWav(filename);
#endif
      SerialPort.println("Replaying file...");
    }
  }
}
