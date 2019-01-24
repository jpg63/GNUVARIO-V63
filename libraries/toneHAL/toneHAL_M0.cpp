#include "toneHAL.h"
#include "toneHAL_M0.h"
#include <Arduino.h>
#include <VarioSettings.h>

#if defined(TONEDAC)

/***********************************/
void ToneHalDAC_Zero::init(void) {
/***********************************/
  privateToneDacZero.init();
}

/***********************************/
void ToneHalDAC_Zero::init(uint32_t pin) {
/***********************************/
  privateToneDacZero.init();
}

/***********************************/
void ToneHalDAC_Zero::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
  privateToneDacZero.init();
}

/***********************************/
void ToneHalDAC_Zero::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
#if defined (TONEDAC_VOLUME) && defined (TONEDAC_LENGTH)
  privateToneDacZero.tone(frequency, _volume*10, 0);
#elseif defined TONEDAC_VOLUME
  privateToneDacZero.tone(frequency, _volume*10);
#else
  privateToneDacZero.tone(frequency);
#endif	
}

/***********************************/
void ToneHalDAC_Zero::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
#if defined (TONEDAC_VOLUME) && defined (TONEDAC_LENGTH)
  privateToneDacZero.tone(frequency, volume*10, 0);
#elseif defined TONEDAC_VOLUME
  privateToneDacZero.tone(frequency, volume*10);
#else
  privateToneDacZero.tone(frequency);
#endif	
}

/***********************************/
void ToneHalDAC_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
#if defined (TONEDAC_VOLUME) && defined (TONEDAC_LENGTH)
  privateToneDacZero.tone(frequency, volume*10, length);
#elseif defined TONEDAC_VOLUME
  privateToneDacZero.tone(frequency, volume*10);
#else
  privateToneDacZero.tone(frequency);
#endif	
}

/***********************************/
void ToneHalDAC_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length, uint8_t background)
/***********************************/
{
	tone(frequency, volume, length);
}

/***********************************/
void ToneHalDAC_Zero::noTone() {
/***********************************/
  privateToneDacZero.noTone();
}

/***********************************/
void ToneHalDAC_Zero::setWaveForm(uint8_t form) {
/***********************************/
  privateToneDacZero.setWaveForm(form);
}
		
/***********************************/
void ToneHalDAC_Zero::beginPlayWav(uint32_t srate)
/***********************************/           
{
	privateToneDacZero.begin(srate);
}

/***********************************/
void ToneHalDAC_Zero::endPlayWav()
/***********************************/          
{
	privateToneDacZero.end();
}

/***********************************/
void ToneHalDAC_Zero::playWav(const char *fname) {
/***********************************/
  privateToneDacZero.play(fname);
}

/***********************************/
bool ToneHalDAC_Zero::isPlayingWav() {
/***********************************/
  return privateToneDacZero.isPlaying();
}

/***********************************/
uint32_t ToneHalDAC_Zero::duration() {
/***********************************/
  return privateToneDacZero.duration();
}

/***********************************/
uint32_t ToneHalDAC_Zero::remaining() {
/***********************************/
  return privateToneDacZero.remaining();
}

#elif defined(TONEAC)

/***********************************/
void ToneHalAC_Zero::init(void) {
/***********************************/
	privateToneAcZero.init();
}

/***********************************/
void ToneHalAC_Zero::init(uint32_t pin) {
/***********************************/
	privateToneAcZero.init();
}

/***********************************/
void ToneHalAC_Zero::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
	privateToneAcZero.init();
}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
  privateToneAcZero.tone(frequency,_volume);	
}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
#ifdef TONEAC_VOLUME
	privateToneAcZero.tone(frequency, _volume);
#else
	privateToneAcZero.tone(frequency);
#endif		
}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
	
#ifdef TONEAC_LENGTH
		  privateToneAcZero.tone(frequency, _volume, length);
#else
#ifdef TONEAC_VOLUME
	privateToneAcZero.tone(frequency, _volume);
#else
	privateToneAcZero.tone(frequency);
#endif	
#endif

}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length, uint8_t background)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
#ifdef TONEAC_LENGTH
		  privateToneAcZero.tone(frequency, _volume, length, background);
#else
#ifdef TONEAC_VOLUME
	privateToneAcZero.tone(frequency, _volume);
#else
	privateToneAcZero.tone(frequency);
#endif	
#endif	
}

/***********************************/
void ToneHalAC_Zero::noTone(void)
/***********************************/           
{
	privateToneAcZero.noTone();
}


#elif defined(TONE)

/***********************************/
void ToneHal_Zero::init(void) {
/***********************************/
  _pin = 2;
}

/***********************************/
void ToneHal_Zero::init(uint32_t pin) {
/***********************************/
  _pin = pin;
}

/***********************************/
void ToneHal_Zero::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
  _pin = pin1;
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
  privateToneZero.tone(_pin,frequency,512);	
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
  privateToneZero.tone(_pin,frequency,512);
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
  privateToneZero.tone(_pin,frequency,length);
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length, uint8_t background)
/***********************************/
{
	tone(frequency, volume, length);
}

/***********************************/
void ToneHal_Zero::noTone(void)
/***********************************/           
{
	privateToneZero.noTone(_pin);
}

#elif defined(TONEI2S)

#endif //Interface type