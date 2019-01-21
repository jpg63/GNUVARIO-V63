#ifndef tone_ZERO_h
#define tone_ZERO_h

#pragma once

#ifdef __cplusplus

#include "Arduino.h"

class ToneZero {

	public:

		void tone(uint32_t _pin, uint32_t frequency, uint32_t duration = 0);
		void noTone(uint32_t _pin);
		
	private:
		uint32_t toneMaxFrequency = F_CPU / 2;
		uint32_t lastOutputPin = 0xFFFFFFFF;
	
		void toneAccurateClock (uint32_t accurateSystemCoreClockFrequency);

};

#endif
#endif
