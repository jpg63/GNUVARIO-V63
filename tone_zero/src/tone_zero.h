/* tone_zero -- library Tone PWM for MKZERO
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
