/* toneAC_zero -- library Tone PWM AC for MKZERO
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
 
#ifndef toneAC_ZERO_h
#define toneAC_ZERO_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#define TONEAC_VOLUME  //set to have volume control
  //#define TONEAC_LENGTH  //set to have length control

	class ToneAcZero {

	public:

		/* must be run before using toneAC */
		void init(void);
  
    void tone(unsigned long frequency = 0
  #ifdef TONEAC_VOLUME
                , uint8_t volume = 10
  #endif
  #ifdef TONEAC_LENGTH
		, unsigned long length = 0, uint8_t background = false
  #endif
		);

    void noTone();
	
/* mute/unmute setting */
    void toneMute(bool newMuteState);
	
  private:
		bool toneACMuted = false;

#ifdef TONEAC_LENGTH
		unsigned long _tAC_time; // Used to track end note with timer when playing note in the background.
#endif

#ifdef TONEAC_VOLUME
//uint8_t _tAC_volume[] = { 200, 100, 67, 50, 40, 33, 29, 22, 11, 2 }; // Duty for linear volume control.
		uint8_t _tAC_volume[10] = { 150, 72, 51, 38, 32, 23, 20, 19, 10, 2 }; //new duty values for three phased Low Power mode
#endif

};

#endif

