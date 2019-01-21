/****************************************************/
/*                                                  */
/*          Libraries ToneHal                       */
/*                                                  */
/*  version    Date     Description                 */
/*    1.0    20/01/19                               */
/*                                                  */
/****************************************************/

#include "toneHAL.h"
#include <Arduino.h>
#include <VarioSettings.h>

/***********************************/
void ToneHal::setVolume(uint8_t newVolume) {
/***********************************/

  _volume = newVolume;
}

/***********************************/
uint8_t ToneHal::getVolume() {
/***********************************/

  return _volume;
}

/***********************************/
void ToneHal::mute(bool newMuteState) {
/***********************************/
  /* stop tone if needed */
  if( newMuteState ) {
    noTone();
  }

  /* save */
  _toneMuted = newMuteState;
}

#if defined(ESP8266) || defined(ESP32)
//********************
// ESP8266 - ESP32
//********************
#if defined(TONEDAC)
#elif defined(TONEAC)
#elif defined(TONE)
#elif defined(TONEI2S)
#endif //Interface type


#elif defined(ARDUINO_AVR_PRO)
//********************
// Pro Mini assignments
//********************
#if defined(TONEDAC)
#elif defined(TONEAC)

/***********************************/
void ToneHalAC_promini::init(void) {
/***********************************/
}

/***********************************/
void ToneHalAC_promini::init(uint32_t pin) {
/***********************************/
}

/***********************************/
void ToneHalAC_promini::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
}

/***********************************/
void ToneHalAC_promini::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
#if defined (TONEAC_LENGTH)
  toneAC(frequency,_volume, 512);
#elif defined(TONEAC_VOLUME)
  toneAC(frequency,_volume);
#else
	toneAc(frequency);
#endif			
}

/***********************************/
void ToneHalAC_promini::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
#ifdef TONEAC_VOLUME
	toneAC(frequency, _volume);
#else
	toneAC(frequency);
#endif		
}

/***********************************/
void ToneHalAC_promini::tone(unsigned long frequency , uint8_t volume, unsigned long length)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
	
#ifdef TONEAC_LENGTH
	toneAC(frequency, _volume, length);
#elseif defined TONEAC_VOLUME
	toneAC(frequency, _volume);
#else
	toneAC(frequency);
#endif	
}

/***********************************/
void ToneHalAC_promini::tone(unsigned long frequency , uint8_t volume, unsigned long length, uint8_t background)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
#ifdef TONEAC_LENGTH
	toneAC(frequency, _volume, length, background);
#elseif defined TONEAC_VOLUME
	toneAC(frequency, _volume);
#else
	toneAC(frequency);
#endif		
}

/***********************************/
void ToneHalAC_promini::noTone(void)
/***********************************/           
{
	noToneAC();
}

/***********************************/
void ToneHalAC_promini::beginPlayWav(uint32_t srate)
/***********************************/           
{
}

/***********************************/
void ToneHalAC_promini::endPlayWav()
/***********************************/          
{
}

/***********************************/
void ToneHalAC_promini::setWaveForm(uint8_t form)
/***********************************/           
{
}

/***********************************/
void ToneHalAC_promini::playWav(const char *fname)
/***********************************/           
{
}

/***********************************/
bool ToneHalAC_promini::isPlayingWav()
/***********************************/           
{
	return false;
}

/***********************************/
uint32_t ToneHalAC_promini::duration()
/***********************************/           
{
	return 0;
}

/***********************************/
uint32_t ToneHalAC_promini::remaining()
/***********************************/           
{
	return 0;
}

#elif defined(TONE)
#elif defined(TONEI2S)
#endif //Interface type

#elif defined(ARDUINO_ARCH_SAMD)
//********************
// MKR ZERO
//********************

#if defined(TONEDAC)

/***********************************/
void ToneHalDAC_Zero::init(void) {
/***********************************/
  ToneDacZero::init();
}

/***********************************/
void ToneHalDAC_Zero::init(uint32_t pin) {
/***********************************/
  ToneDacZero::init();
}

/***********************************/
void ToneHalDAC_Zero::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
  ToneDacZero::init();
}

/***********************************/
void ToneHalDAC_Zero::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
#if defined (TONEDAC_VOLUME) && defined (TONEDAC_LENGTH)
  ToneDacZero::tone(frequency, _volume*10, 0);
#elseif defined TONEDAC_VOLUME
  ToneDacZero::tone(frequency, _volume*10);
#else
  ToneDacZero::tone(frequency);
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
  ToneDacZero::tone(frequency, volume*10, 0);
#elseif defined TONEDAC_VOLUME
  ToneDacZero::tone(frequency, volume*10);
#else
  ToneDacZero::tone(frequency);
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
  ToneDacZero::tone(frequency, volume*10, length);
#elseif defined TONEDAC_VOLUME
  ToneDacZero::tone(frequency, volume*10);
#else
  ToneDacZero::tone(frequency);
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
  ToneDacZero::noTone();
}

/***********************************/
void ToneHalDAC_Zero::setWaveForm(uint8_t form) {
/***********************************/
  ToneDacZero::setWaveForm(form);
}
		
/***********************************/
void ToneHalDAC_Zero::beginPlayWav(uint32_t srate)
/***********************************/           
{
	ToneDacZero::begin(srate);
}

/***********************************/
void ToneHalDAC_Zero::endPlayWav()
/***********************************/          
{
	ToneDacZero::end();
}

/***********************************/
void ToneHalDAC_Zero::playWav(const char *fname) {
/***********************************/
  ToneDacZero::play(fname);
}

/***********************************/
bool ToneHalDAC_Zero::isPlayingWav() {
/***********************************/
  return ToneDacZero::isPlaying();
}

/***********************************/
uint32_t ToneHalDAC_Zero::duration() {
/***********************************/
  return ToneDacZero::duration();
}

/***********************************/
uint32_t ToneHalDAC_Zero::remaining() {
/***********************************/
  return ToneDacZero::remaining();
}

#elif defined(TONEAC)

/***********************************/
void ToneHalAC_Zero::init(void) {
/***********************************/
	ToneAcZero::init();
}

/***********************************/
void ToneHalAC_Zero::init(uint32_t pin) {
/***********************************/
	ToneAcZero::init();
}

/***********************************/
void ToneHalAC_Zero::init(uint32_t pin1, uint32_t pin2) {
/***********************************/
	ToneAcZero::init();
}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency)
/***********************************/           
{
	if (_toneMuted) return;
  ToneAcZero::tone(frequency,_volume);	
}

/***********************************/
void ToneHalAC_Zero::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
#ifdef TONEAC_VOLUME
	ToneAcZero::tone(frequency, _volume);
#else
	ToneAcZero::tone(frequency);
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
		  ToneAcZero::tone(frequency, _volume, length);
#else
#ifdef TONEAC_VOLUME
	ToneAcZero::tone(frequency, _volume);
#else
	ToneAcZero::tone(frequency);
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
		  ToneAcZero::tone(frequency, _volume, length, background);
#else
#ifdef TONEAC_VOLUME
	ToneAcZero::tone(frequency, _volume);
#else
	ToneAcZero::tone(frequency);
#endif	
#endif	
}

/***********************************/
void ToneHalAC_Zero::noTone(void)
/***********************************/           
{
	ToneAcZero::noTone();
}

/***********************************/
void ToneHalAC_Zero::beginPlayWav(uint32_t srate)
/***********************************/           
{
}

/***********************************/
void ToneHalAC_Zero::endPlayWav()
/***********************************/          
{
}

/***********************************/
void ToneHalAC_Zero::setWaveForm(uint8_t form)
/***********************************/           
{
}

/***********************************/
void ToneHalAC_Zero::playWav(const char *fname)
/***********************************/           
{
}

/***********************************/
bool ToneHalAC_Zero::isPlayingWav()
/***********************************/           
{
	return false;
}

/***********************************/
uint32_t ToneHalAC_Zero::duration()
/***********************************/           
{
	return 0;
}

/***********************************/
uint32_t ToneHalAC_Zero::remaining()
/***********************************/           
{
	return 0;
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
  ToneZero::tone(_pin,frequency,512);	
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency , uint8_t volume)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
  ToneZero::tone(_pin,frequency,512);
}

/***********************************/
void ToneHal_Zero::tone(unsigned long frequency , uint8_t volume, unsigned long length)
/***********************************/           
{
	if (_toneMuted) return;
	if (volume > 10) volume = 10;
	_volume = volume;
	if (length > 1024) length = 1024;
  ToneZero::tone(_pin,frequency,length);
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
	ToneZero::noTone(_pin);
}

/***********************************/
void ToneHal_Zero::beginPlayWav(uint32_t srate)
/***********************************/           
{
}

/***********************************/
void ToneHal_Zero::endPlayWav()
/***********************************/           
{
}

/***********************************/
void ToneHal_Zero::setWaveForm(uint8_t form)
/***********************************/           
{
}

/***********************************/
void ToneHal_Zero::playWav(const char *fname)
/***********************************/           
{
}

/***********************************/
bool ToneHal_Zero::isPlayingWav()
/***********************************/           
{
	return false;
}

/***********************************/
uint32_t ToneHal_Zero::duration()
/***********************************/           
{
	return 0;
}

/***********************************/
uint32_t ToneHal_Zero::remaining()
/***********************************/           
{
	return 0;
}


#elif defined(TONEI2S)

#endif //Interface type

#else

#endif //microcontroler type
