#ifndef tone_ZERO_h
#define tone_ZERO_h

// ---------------------------------------------------------------------------
//
// SOUND Library Tone for MK0
//
// ----------------------------------------------------------------------------

/***********************************************************************************/
/*                                                                                 */
/*                           Libraries tone_zero                                   */
/*                                                                                 */
/*  version    Date          Description                                           */
/*    1.0.0    20/01/19				                                                     */
/*    1.0.1    10/06/19      Ajout gestion ampli class D externe                   */
/*                                                                                 */
/***********************************************************************************/

#pragma once

#ifdef __cplusplus

#include "Arduino.h"

class ToneZero {

	public:
		void init(void);

		void tone(uint32_t _pin, uint32_t frequency, uint32_t duration = 0);
		void noTone(uint32_t _pin);
			
	private:
		uint32_t toneMaxFrequency = F_CPU / 2;
		uint32_t lastOutputPin = 0xFFFFFFFF;
	
		void toneAccurateClock (uint32_t accurateSystemCoreClockFrequency);

};

#endif
#endif
