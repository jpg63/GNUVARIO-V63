/* toneDAC_zero -- library Tone DAC for MKZERO
 *
 * Copyright 2019 Jean-philippe GOI
 * 
 * This file is part of Tone_zero.
 *
 * tone_zero is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tone_zero is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
 
#ifndef toneDAC_ZERO_h
#define toneDAC_ZERO_h

/****************************************************/
/*                                                  */
/*          Libraries ToneDAC                       */
/*                                                  */
/*  version    Date     Description                 */
/*    1.0    20/01/19                               */
/*    1.1    26/01/19   petites modifications       */
/*    1.2    02/03/19   Ajout TONEDAC_EXTENDED      */
/*                                                  */
/****************************************************/

#include <Arduino.h>

#define TONEDAC_VOLUME  //set to have volume control
//#define TONEDAC_LENGTH  //set to have length control
//#define TONEDAC_EXTENDED

#define WAVEFORM_SINUS			1
#define WAVEFORM_TRIANGLE		2
#define WAVEFORM_SQUARE			3
#define WAVEFORM_WAV 				4
	
#define SAMPLERATE  				120000
#define SAMPLECOUNT					256
	
#if defined(TONEDAC_EXTENDED)
#include <SPI.h>
#include "SdFat.h"
#endif //HAVE_SDCARD

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

#if defined(TONEDAC_EXTENDED)
		
    void play(const char *fname) ;
    bool isPlaying();
    uint32_t duration();
    uint32_t remaining();
#endif //TONEDAC_EXTENDED

		uint8_t getVolume();
		
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

#if defined(TONEDAC_EXTENDED)
//extern Class_ToneDac toneDAC;
extern SdFat SD;
#endif //TONEDAC_EXTENDED

#endif
	
	


