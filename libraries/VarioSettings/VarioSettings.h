#ifndef VARIO_SETTINGS_H
#define VARIO_SETTINGS_H

#include <Arduino.h>
#include <SPI.h>
//#include <SD.h>
#include "SdFat.h"

/*----------------------------*/
/*          SOFTWARE          */
/*      Vario parameters      */
/*                            */
/*----------------------------*/

#define VARIOMETER_MODEL "GNUVario"

/*----------------------------*/
/*          HARDWARE          */
/*      Vario parameters      */
/*                            */
/*----------------------------*/

/* Comment or uncomment according to  */
/* what you embed in the variometer   */ 
#define HAVE_SPEAKER
#define HAVE_ACCELEROMETER
#define HAVE_SCREEN
#define HAVE_GPS
#define HAVE_SDCARD
//#define HAVE_BLUETOOTH
#define HAVE_VOLTAGE_DIVISOR


//#define HAVE_TONE
//#define HAVE_TONEDAC

// CJMCU-117 MPU9250+MS5611 circuit interface
//
// VCC  VCC
// GND  GND
//
// MS5611 - MPU9250			WIRE/I2C (SERCOM0)
// SCL  D12 		SCL			WIRE/I2C - SERCOM0
// SDA  D11 		SDA			MS5611 / MPU9250
//
// SWITCHS
// 				A1,A2 				Switch
// 				D5    				Switch Droite - Power
//
// RST   	A4		 	Reset
//
// E-Ink								SPI (SERCOM1)
// CS    	D4
// BUSY  	D3
// RST   	A3
// DC    	D7
// DIN   	MOSI/D8
// CLK   	SCK/D9
//
// GPS	FGPMMOPA6C, construite autour du jeu de puces MTK3339		Serial1 (SERCOM5)
// TX    	D14						serial1  
// RX     D13 					Serial1     
//
// Bluetooth / Microship RN4871		SERIAL (SERCOM3)
// TX    	D0 						sercom3
// RX    	D1 						sercom3
// 				A5						RN4871:RST
//				A6						RN4871:INT		sleep / wake manager
// 
// SD-CARD		SPI (SERCOM2)
// MOSI		MOSI					SD SPI
// SCL		SCK						SD SPI
// SS			SS						SD SPI	
// MISO		MISO					SD SPI
// CD			CD						SD SPI
//
// Buzzer
//    		D2						PWM
//
//				A0/DAC0				DAC0
//				D6						Mute Max
//
// ADC_BATTERY					Battery voltage
// LED_BUILTIN					LED

/* Set the pins used for Screen modules */


#if defined(ESP8266)

// generic/common.h
//static const uint8_t SS    = 15;
//static const uint8_t MOSI  = 13;
//static const uint8_t MISO  = 12;
//static const uint8_t SCK   = 14;
// pins_arduino.h
//static const uint8_t D8   = 15;
//static const uint8_t D7   = 13;
//static const uint8_t D6   = 12;
//static const uint8_t D5   = 14;

//GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
//GxIO_Class io(SPI, SS, D3, D4);
// GxGDEP015OC1(GxIO& io, uint8_t rst = D4, uint8_t busy = D2);
//GxEPD_Class display(io);
// or my IoT connection, busy on MISO
//GxEPD_Class display(io, D4, D6);

#define VARIOSCREEN_CS_PIN SS
#define VARIOSCREEN_DC_PIN D3
#define VARIOSCREEN_RST_PIN D4


#elif defined(ESP32)

// pins_arduino.h, e.g. LOLIN32
//static const uint8_t SS    = 5;
//static const uint8_t MOSI  = 23;
//static const uint8_t MISO  = 19;
//static const uint8_t SCK   = 18;

//GxIO_Class io(SPI, SS, 17, 16);
//GxEPD_Class display(io, 16, 4);

#define VARIOSCREEN_CS_PIN SS
#define VARIOSCREEN_DC_PIN 17
#define VARIOSCREEN_RST_PIN 16
#define VARIOSCREEN_BUSY_PIN 4

#elif defined(ARDUINO_ARCH_SAMD)

// variant.h of MKR1000
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (24u) // should be 4?
// variant.h of MKRZERO
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (4u)

//GxIO_Class io(SPI, 4, 7, 6);
//GxEPD_Class display(io, 6, 5);

#define VARIOSCREEN_CS_PIN 4   
#define VARIOSCREEN_DC_PIN 7
#define VARIOSCREEN_RST_PIN A3
#define VARIOSCREEN_BUSY_PIN 3
//#define VARIOSCREEN_BUSY_PIN 5

#elif defined(_BOARD_GENERIC_STM32F103C_H_)

// STM32 Boards (STM32duino.com)
// Generic STM32F103C series
// aka BluePill
// board.h
//#define BOARD_SPI1_NSS_PIN        PA4
//#define BOARD_SPI1_MOSI_PIN       PA7
//#define BOARD_SPI1_MISO_PIN       PA6
//#define BOARD_SPI1_SCK_PIN        PA5
//enum {
//    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,PA14,PA15,
//  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,PB14,PB15,
//  PC13, PC14,PC15
//};
// variant.h
//static const uint8_t SS   = BOARD_SPI1_NSS_PIN;
//static const uint8_t SS1  = BOARD_SPI2_NSS_PIN;
//static const uint8_t MOSI = BOARD_SPI1_MOSI_PIN;
//static const uint8_t MISO = BOARD_SPI1_MISO_PIN;
//static const uint8_t SCK  = BOARD_SPI1_SCK_PIN;

//GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
//GxIO_Class io(SPI, SS, 8, 9);
//  GxGDEP015OC1(GxIO& io, uint8_t rst = 9, uint8_t busy = 7);
//GxEPD_Class display(io, 9, 3);
#define VARIOSCREEN_CS_PIN SS
#define VARIOSCREEN_DC_PIN 8
#define VARIOSCREEN_RST_PIN 9
#define VARIOSCREEN_BUSY_PIN 3

#else

// pins_arduino.h, e.g. AVR
//#define PIN_SPI_SS    (10)
//#define PIN_SPI_MOSI  (11)
//#define PIN_SPI_MISO  (12)
//#define PIN_SPI_SCK   (13)

//GxIO_Class io(SPI, SS, 8, 9);
//GxIO_DESTM32L io;
//GxIO_GreenSTM32F103V io;
//GxEPD_Class display(io);

#define VARIOSCREEN_CS_PIN SS
#define VARIOSCREEN_DC_PIN 8
#define VARIOSCREEN_RST_PIN 9

#endif

#if defined(ESP8266)

#elif defined(ESP32)

#elif defined(ARDUINO_ARCH_SAMD)
#define SDCARD_CS_PIN SDCARD_SS_PIN
#elif defined(_BOARD_GENERIC_STM32F103C_H_)

#elif defined(ARDUINO_AVR_PRO)
#define SDCARD_CS_PIN 14
#else

#endif


/*int pinSDA = 11;
int pinSCL = 12;*/
//#define VARIODRDY_INT_PIN 3
//#define VARIOAUDIO_PWM1_PIN A3
//#define VARIOAUDIO_PWM2_PIN A4
#define VARIOBTN_LEFT_PIN A2
#define VARIOBTN_CENTER_PIN A1
#define VARIOBTN_RIGHT_PIN D5

/*interrupts in the Zero variant:

EXTERNAL_INT_2: A0, A5, 10
EXTERNAL_INT_4: A3, 6
EXTERNAL_INT_5: A4, 7
EXTERNAL_INT_6: 8, SDA
EXTERNAL_INT_7: 9, SCL
EXTERNAL_INT_9: A2, 3
EXTERNAL_INT_10: TX, MOSI
EXTERNAL_INT_11: RX, SCK*/

#define VARIOPOWER_INT_PIN 6
//const byte interruptPin = A5;

//#define VARIO_DETECT_USB A6
#define VARIO_PIN_ALIM   D5
#define VARIO_PIN_RST    A4
// A6    Detection de connection USB
// A5    Commande de l'alimentation des cartes


/* The voltage divisor */

#if defined(ESP8266)

#elif defined(ESP32)

#elif defined(ARDUINO_ARCH_SAMD)
#define VOLTAGE_DIVISOR_PIN ADC_BATTERY
#elif defined(_BOARD_GENERIC_STM32F103C_H_)

#elif defined(ARDUINO_AVR_PRO)
#define VOLTAGE_DIVISOR_PIN 16
#else

#endif

#define VOLTAGE_DIVISOR_VALUE 1.27
#define VOLTAGE_DIVISOR_REF_VOLTAGE 3.3

/*****************************/
/* SDCard/Bluetooth behavior */
/*****************************/

/* What type of barometric altitude is sent :           */
/* -> Based on international standard atmosphere        */
/* -> Calibrated with GPS altitude                      */
//#define VARIOMETER_SDCARD_SEND_CALIBRATED_ALTITUDE
//#define VARIOMETER_BLUETOOTH_SEND_CALIBRATED_ALTITUDE

/* The bauds rate used by the GPS and Bluetooth modules. */
/* GPS and bluetooth need to have the same bauds rate.   */
#define GPS_BLUETOOTH_BAUDS 9600

/* What type of vario NMEA sentence is sent by bluetooth. */
/* Possible values are :                                  */
/*  - VARIOMETER_SENT_LXNAV_SENTENCE                      */
/*  - VARIOMETER_SENT_LK8000_SENTENCE                     */
#define VARIOMETER_SENT_LK8000_SENTENCE


/* When there is no GPS to sync variometer bluetooth sentences */
/* set the delay between sendings in milliseconds.             */ 
#define VARIOMETER_SENTENCE_DELAY 2000

// Accelerometer type
#define MPU9250

/* calibration method */
// by EEPROM
//#define IMU_CALIBRATION_IN_EEPROM
// or by static value

/* Parametre par defaut */
/*#define IMU_GYRO_CAL_BIAS {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define IMU_ACCEL_CAL_BIAS {0, 0, 0}
#define IMU_ACCEL_CAL_SCALE 0
#define IMU_MAG_CAL_BIAS {0, 0, 0}
#define IMU_MAG_CAL_PROJ_SCALE -166*/

//Version 2
#define IMU_GYRO_CAL_BIAS {0x00, 0x00, 0x1b, 0x92, 0x00, 0x00, 0x23, 0x4f, 0x00, 0x01, 0x1c, 0x7f}
#define IMU_ACCEL_CAL_BIAS {3042, 7981, 1753}
#define IMU_ACCEL_CAL_SCALE -288
#define IMU_MAG_CAL_BIAS {9049, 7449, 6753}
#define IMU_MAG_CAL_PROJ_SCALE -3384

//Version 3
//#define IMU_GYRO_CAL_BIAS {0x00, 0x00, 0x3f, 0xf0, 0xff, 0xff, 0xb8, 0x17, 0xff, 0xff, 0xa8, 0x2c}
//#define IMU_ACCEL_CAL_BIAS {-1943, 4749, -15216}
//#define IMU_ACCEL_CAL_SCALE -140
//#define IMU_MAG_CAL_BIAS {45, 3697, 2482}
//#define IMU_MAG_CAL_PROJ_SCALE -9714


/********************/
/* Measure behavior */
/********************/

/* Speed filtering :                                               */
/* Greater values give smoother speed. The base unit is 2 seconds  */
/* so size = 5 use the last 10 seconds to average speed.           */
#define VARIOMETER_SPEED_FILTER_SIZE 5

/* Set the GPS precision needed to use the GPS altitude value  */
/* to calibrate the barometric altitude.                       */
/*      !!! the best possible precision is 100 !!!             */ 
#define VARIOMETER_GPS_ALTI_CALIBRATION_PRECISION_THRESHOLD 200

/* SPI speed                                 */
/* The variometer seems to be more stable at */
/* half speed. Don't hesitate to experiment. */
/*#if F_CPU >= 16000000L
#define VARIOSCREEN_SPEED SPI_CLOCK_DIV4
#define SDCARD_SPEED SPI_CLOCK_DIV4
#else
#define VARIOSCREEN_SPEED SPI_CLOCK_DIV2
#define SDCARD_SPEED SPI_CLOCK_DIV2
#endif //CPU_FREQ*/

// print useful information to the serial port for 
// verifying correct operation. Comment out to prevent
// data being spewed out continuously.


//Monitor Port 
#if defined(ESP8266)

#elif defined(ESP32)

#elif defined(ARDUINO_ARCH_SAMD)
#define SerialPort SerialUSB
#elif defined(_BOARD_GENERIC_STM32F103C_H_)

#elif defined(ARDUINO_AVR_PRO)
#define SerialPort Serial
#else
#define SerialPort Serial
#endif



/* Set the Sercom and the pins used by GPS/Bluetooth */
/* See p21 of the datasheet                          */
#define VARIOMETER_SERIAL_SERCOM SERCOM4
#define VARIOMETER_SERIAL_TX_PIN 4
#define VARIOMETER_SERIAL_RX_PIN 5
#define VARIOMETER_SERIAL_PIN_FUNCTION PIO_SERCOM_ALT
#define VARIOMETER_SERIAL_TX_PAD UART_TX_PAD_2
#define VARIOMETER_SERIAL_RX_PAD SERCOM_RX_PAD_3

/* Model GPS */
//#define VARIOMETER_GPS_NEO6
#define VARIOMETER_GPS_NEO8

/* I2C speed                                   */
/* You can try 800 on <8mhz microcontrollers   */ 
/* (Not always work)                           */
#define FASTWIRE_SPEED 400

/* eeprom sound setting adresses */
#define SOUND_EPROM_TAG 9806
#define SOUND_EPROM_ADDR 0x10

#define VARIO_PIN_BUZZER    2

//              DEBUGING MODE
#define IMU_DEBUG			  //debug IMU
#define PROG_DEBUG			  //debug principal program
#define I2CDEV_SERIAL_DEBUG   //debug I2Cdev
#define DEGUB_SERIAL_NMEA_1
//#define SCREEN_DEBUG
#define GPS_DEBUG
#define BUTTON_DEBUG
#define TONEDAC_DEBUG


extern SdFat SD;

/******************************************************/
/******************************************************/


class VarioSettings {

 public:
  boolean initSettings();
  boolean readSDSettings();
  boolean readFlashSDSettings();
  void writeFlashSDSettings();
  uint8_t soundSettingRead(void);
  void soundSettingWrite(uint8_t volume);

#ifdef IMU_DEBUG 
  int exINT = 15;
  float exFloat = 1.12345;
  boolean exBoolean = true;
  long exLong = 2123456789;
#endif //IMU_DEBUG
  
  String VARIOMETER_PILOT_NAME = "Magali";
  String VARIOMETER_GLIDER_NAME = "MAC-PARA Muse 3";
  
  /* time zone relative to UTC */
  int8_t VARIOMETER_TIME_ZONE = (+2); 

  /*******************/
/* Screen behavior */
/*******************/

/* the duration of the two screen pages in milliseconds */
  int16_t VARIOMETER_BASE_PAGE_DURATION = 3000;
  int16_t VARIOMETER_ALTERNATE_PAGE_DURATION =3000;

  /*********/
  /* Beeps */
  /*********/

  /* The volume of the beeps, max = 10 */
  uint8_t VARIOMETER_BEEP_VOLUME = 3;

  /* The variometer react like this according to vertical speed in m/s :        */
  /* (near climbing beep is not enabled by default)                             */
  /*                                                                            */
  /* <--LOW-BEEP--|------SILENT------|--NEAR-CLIMBING-BEEP--|--CLIMBING-BEEP--> */
  /*              |                  |                      |                   */
  /*           SINKING         CLIMBING-SENSITIVITY      CLIMBING               */
  float VARIOMETER_SINKING_THRESHOLD =-2.0;
  float VARIOMETER_CLIMBING_THRESHOLD=0.2;
  float VARIOMETER_NEAR_CLIMBING_SENSITIVITY=0.5; 
  
  /* The near climbing alarm : signal that you enter or exit the near climbing zone */
  /* The near climbing beep : beep when you are in near climbing zone               */
  boolean VARIOMETER_ENABLE_NEAR_CLIMBING_ALARM = false;
  boolean VARIOMETER_ENABLE_NEAR_CLIMBING_BEEP  = false;

  /********************/
  /* Measure behavior */
  /********************/

  /* Flight start detection conditions :                      */
  /* -> Minimum time after poweron in milliseconds            */
  /* -> Minimum vertical velocity in m/s (low/high threshold) */
  /* -> Minimum ground speed in km/h                          */
  long FLIGHT_START_MIN_TIMESTAMP = 15000;
  float FLIGHT_START_VARIO_LOW_THRESHOLD = (-0.5);
  float FLIGHT_START_VARIO_HIGH_THRESHOLD = 0.5;
  float FLIGHT_START_MIN_SPEED = 8.0;

  /* GPS track recording on SD card starting condition :  */ 
  /* -> As soon as possible (GPS fix)                     */
  /* -> When flight start is detected                     */
   boolean VARIOMETER_RECORD_WHEN_FLIGHT_START = true;

  /* What type of vario NMEA sentence is sent by bluetooth. */
  /* Possible values are :                                  */
  /*  - VARIOMETER_SENT_LXNAV_SENTENCE                      */
  /*  - VARIOMETER_SENT_LK8000_SENTENCE                     */
  //boolean VARIOMETER_SENT_LXNAV_SENTENCE = true;

  /* Alarm */
  /* Alarm SDCARD not insert */
  boolean ALARM_SDCARD = true;
  /* Alarm GPS Fix */
  boolean ALARM_GPSFIX = true;
  /* Alarm Fly begin */
  boolean ALARM_FLYBEGIN = true;

// Kalman filter configuration
  float KF_ZMEAS_VARIANCE  =     400.0f;
  float KF_ZACCEL_VARIANCE =     1000.0f;
  float KF_ACCELBIAS_VARIANCE   = 1.0f;

// Power-down timeout. Here we power down if the
// vario does not see any climb or sink rate more than
// 50cm/sec, for 20 minutes.
   uint16_t SLEEP_TIMEOUT_SECONDS   = 1200; // 20 minutes
   uint8_t  SLEEP_THRESHOLD_CPS		= 50;

// vario thresholds in cm/sec for generating different
// audio tones. Between the sink threshold and the zero threshold,
// the vario is quiet
/*                                                                            */
/* <--LOW-BEEP--|------SILENT------|--NEAR-CLIMBING-BEEP--|--CLIMBING-BEEP--> */
/*              |                  |                      |                   */
/*             SINK              ZERO                   CLIMB                 */
   uint8_t CLIMB_THRESHOLD   =   50;
   int8_t ZERO_THRESHOLD	 =    5;
   int16_t SINK_THRESHOLD    =   -250;

// change these parameters based on the frequency bandwidth of the speaker

    uint16_t VARIO_MAX_FREQHZ   =   4000;
    uint16_t VARIO_XOVER_FREQHZ =   2000;
    uint16_t VARIO_MIN_FREQHZ   =   200;

    uint16_t VARIO_SINK_FREQHZ  =   400;
    uint16_t VARIO_TICK_FREQHZ  =   200;

// audio feedback tones
    uint16_t BATTERY_TONE_FREQHZ	=	400;
    uint16_t CALIB_TONE_FREQHZ		=	800;
    uint16_t MPU9250_ERROR_TONE_FREQHZ	= 200;
    uint16_t MS5611_ERROR_TONE_FREQHZ	= 2500;
    uint16_t SDCARD_ERROR_TONE_FREQHZ	= 2000;  
	uint16_t BEEP_FREQ                  = 800;
	
//Setting accelerometer
    double ACCELCALX = 0.0;
	double ACCELCALY = 0.0;
	double ACCELCALZ = 0.0;
  
 protected:
  File myFile;
//  File myFile2;
  char FileName[15] = "SETTINGS.TXT";
  char FileFlashName[15] = "FLASH.TXT";
  
  void applySetting(String settingName, String settingValue);
  void applyFlashSetting(String settingName, String settingValue);
  float toFloat(String settingValue);
  long toLong(String settingValue);
  boolean toBoolean(String settingValue);
};

extern VarioSettings GnuSettings;

class Statistic {

 public:
   void setTime(int8_t* timeValue);
   int8_t* getTime(void);
   int8_t* getTime(int8_t* timeValue);
   void setDuration(int8_t* durationValue);
   int8_t* getDuration(void);
   int8_t* getDuration(int8_t* durationValue);
   void setAlti(double alti);
   double getMaxAlti(void);
   double getMinAlti(void);
   void setVario(double vario);
   double getMaxVario(void);
   double getMinVario(void);
   void setSpeed(double speed);
   double getMaxSpeed(void);
   double getMinSpeed(void);
   double getAltiDeco(void);
   double getGain(void);

  private:
    int8_t time[3];
	int8_t duration[3];

    double currentSpeed=0;
    double maxSpeed;
    double minSpeed;
    double currentAlti=0;
    double maxAlti;
    double minAlti;
	double currentVario=0;
	double maxVario;
	double minVario;
	
	double altiDeco;
	double gain;
};

#endif
