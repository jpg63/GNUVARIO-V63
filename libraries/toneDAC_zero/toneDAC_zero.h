#ifndef toneDAC_ZERO_h
#define toneDAC_ZERO_h

#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

  #define TONEDAC_VOLUME  //set to have volume control
  //#define TONEDAC_LENGTH  //set to have length control

  #define WAVEFORM_SINUS			1
  #define WAVEFORM_TRIANGLE		2
  #define WAVEFORM_SQUARE			3
  #define WAVEFORM_WAV 				4
	
	#define SAMPLERATE  				120000
	#define SAMPLECOUNT					256
	
	void TC5_Handler();

class ToneDacZero {

	public:
		uint32_t 	fileSize = 0;
 		uint32_t 	sampleRate = 120000; //sample rate of the sine wave
 
    void init(void);
	  void begin(uint32_t srate);
		void end();
    void tone(unsigned long frequency = 0
  #ifdef TONEDAC_VOLUME
                , uint8_t volume = 100
  #endif
  #ifdef TONEDAC_LENGTH
		, unsigned long length = 0, uint8_t background = false
  #endif
		);

    void noTone();
        /* mute/unmute setting */
    void toneMute(bool newMuteState);
		void setWaveForm(uint8_t form);
    void play(const char *fname) ;
    bool isPlaying();
    uint32_t duration();
    uint32_t remaining();
			
	private:

		bool 			toneDACMuted = false;
		uint32_t 	multiplicateur;
		uint32_t 	_frequency;
		
		void genForm(int sCount);
		void genSin(int sCount);
		void genSquare(int sCount);
		void genTriangle(int sCount);

		void tcReset();
		void tcDisable();
		void tcConfigure(int sampleRate);
		void tcStartCounter();
		bool tcIsSyncing();
		
#ifdef TONEDAC_LENGTH
		unsigned long _tDAC_time; // Used to track end note with timer when playing note in the background.
#endif

		uint8_t _tDAC_volume = 100; //new duty values for three phased Low Power mode
};

//extern Class_ToneDac toneDAC;
extern SdFat SD;

#endif
	
	


