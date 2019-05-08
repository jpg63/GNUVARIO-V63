#ifndef _HARDWARECONFIGESP32_H_
#define _HARDWARECONFIGESP32_H_

#if defined(ESP32)

/******************************/
/*            SCREEN          */
/******************************/

/* Set the pins used for Screen modules */

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



/****************************/
/*           SDCARD         */
/****************************/

#define SDCARD_CS_PIN SDCARD_SS_PIN

/***************************/
/*        LED              */
/***************************/

#define pinLED (22)

#define LED_ON() 		   {GPIO.out_w1ts = (1 << pinLED);}
#define LED_OFF()		   {GPIO.out_w1tc = (1 << pinLED);}

/****************************/
/*           Buttons        */
/****************************/

#define VARIOBTN_LEFT_PIN A2
#define VARIOBTN_CENTER_PIN A1
#define VARIOBTN_RIGHT_PIN D5

/***********************/
/* The voltage divisor */
/***********************/

#define VOLTAGE_DIVISOR_PIN 16

/*************************/
/*        GPS            */
/*************************/

#define pinGpsTXD  (21)
#define pinGpsRXD  (22)
#define pinGpsRTS  (-1)
#define pinGpsCTS  (-1)

#define GPS_UART_NUM          UART_NUM_1
//#define UART_RX_BUFFER_SIZE   512
#define UART_RX_BUFFER_SIZE   256

/*************************/
/*         AUDIO         */
/*************************/

#define pinAudioAmpEna       (32)
//#define pinAudioDAC          (25)
#define SPEAKER_PIN 25		//or 26
#define TONE_PIN_CHANNEL 0	// or 1


#endif
#endif