#ifndef toneHAL_h
#define toneHAL_h

#include <Arduino.h>
#include <VarioSettings.h>


#define WAVEFORM_SINUS			1
#define WAVEFORM_TRIANGLE		2
#define WAVEFORM_SQUARE			3
#define WAVEFORM_WAV 				4

	
#define DEFAULT_VOLUME 			5

//#define TONEI2S
#define	TONEDAC
//#define	TONEAC
//#define TONE

class ToneHal  {

	public:

		virtual void init(void) = 0;
		virtual void init(uint32_t pin) = 0;
    virtual void init(uint32_t pin1, uint32_t pin2) = 0;
    virtual void tone(unsigned long frequency) = 0;
    virtual void tone(unsigned long frequency, uint8_t volume) = 0;
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length) = 0;
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background) = 0;

		virtual void noTone() = 0;

		//select form signal - sinus,triangle, square or wav
		virtual void setWaveForm(uint8_t form) = 0;

		//Function play wav file 
	  virtual void beginPlayWav(uint32_t srate) = 0;
		virtual void endPlayWav() = 0;
    virtual void playWav(const char *fname) = 0;
    virtual bool isPlayingWav() = 0;
    virtual uint32_t duration() = 0;;
    virtual uint32_t remaining() = 0;		

		//Volume 
		void setVolume(uint8_t newVolume = DEFAULT_VOLUME);
    uint8_t getVolume();

		    /* mute/unmute setting */
    void mute(bool newMuteState);

	protected:
		uint8_t _volume = 10;	
		bool 		_toneMuted = false;

};

#if defined(ESP8266) || defined(ESP32)
//********************
// ESP8266 - ESP32
//********************

#elif defined(ARDUINO_AVR_PRO)
//********************
// Pro Mini assignments
//********************

#if defined(TONEDAC)

#elif defined(TONEAC)
#include "toneAC.h"

class ToneHalAC_promini : public ToneHal {
	public:

		virtual void init(void);
		virtual void init(uint32_t pin);
    virtual void init(uint32_t pin1, uint32_t pin2);
    virtual void tone(unsigned long frequency);
    virtual void tone(unsigned long frequency, uint8_t volume);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);

		virtual void noTone();

		virtual void setWaveForm(uint8_t form);

	  virtual void beginPlayWav(uint32_t srate);
		virtual void endPlayWav();
    virtual void playWav(const char *fname) ;
    virtual bool isPlayingWav();
    virtual uint32_t duration();
    virtual uint32_t remaining();		
		
	protected:
		uint32_t _pin;
};	

#define ToneHAL ToneHalAC_promini	

#elif defined(TONE)

#endif //Interface type

#elif defined(ARDUINO_ARCH_SAMD)
//********************
// MKR ZERO
//********************

#if defined(TONEDAC)
#include <toneDAC_zero.h>

class ToneHalDAC_Zero : public ToneHal, public ToneDacZero {
	public:

		virtual void init(void);
		virtual void init(uint32_t pin);
    virtual void init(uint32_t pin1, uint32_t pin2);
    virtual void tone(unsigned long frequency);
    virtual void tone(unsigned long frequency, uint8_t volume);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);

		virtual void noTone();

		virtual void setWaveForm(uint8_t form);

	  virtual void beginPlayWav(uint32_t srate);
		virtual void endPlayWav();
    virtual void playWav(const char *fname) ;
    virtual bool isPlayingWav();
    virtual uint32_t duration();
    virtual uint32_t remaining();		
};	
	
#define ToneHAL ToneHalDAC_Zero	
	
#elif defined(TONEAC)
#include <toneAC_zero.h>

class ToneHalAC_Zero : public ToneHal, public ToneAcZero {
	public:

		virtual void init(void);
		virtual void init(uint32_t pin);
    virtual void init(uint32_t pin1, uint32_t pin2);
    virtual void tone(unsigned long frequency);
    virtual void tone(unsigned long frequency, uint8_t volume);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);

		virtual void noTone();

		virtual void setWaveForm(uint8_t form);

	  virtual void beginPlayWav(uint32_t srate);
		virtual void endPlayWav();
    virtual void playWav(const char *fname) ;
    virtual bool isPlayingWav();
    virtual uint32_t duration();
    virtual uint32_t remaining();		
};	

#define ToneHAL ToneHalAC_Zero	

#elif defined(TONE)
#include <tone_zero.h>

class ToneHal_Zero : public ToneHal, public ToneZero {
	public:

		virtual void init(void);
		virtual void init(uint32_t pin);
    virtual void init(uint32_t pin1, uint32_t pin2);
    virtual void tone(unsigned long frequency);
    virtual void tone(unsigned long frequency, uint8_t volume);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);

		virtual void noTone();

		virtual void setWaveForm(uint8_t form);

	  virtual void beginPlayWav(uint32_t srate);
		virtual void endPlayWav();
    virtual void playWav(const char *fname) ;
    virtual bool isPlayingWav();
    virtual uint32_t duration();
    virtual uint32_t remaining();		
		
	protected:
		uint32_t _pin;
};	

#define ToneHAL ToneHal_Zero	

#elif defined(TONEI2S)

class ToneHalI2S_Zero : ToneHal{
	public:

		virtual void init(void);
		virtual void init(uint32_t pin);
    virtual void init(uint32_t pin1, uint32_t pin2);
    virtual void tone(unsigned long frequency);
    virtual void tone(unsigned long frequency, uint8_t volume);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length);
    virtual void tone(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background);

		virtual void noTone();

		virtual void setWaveForm(uint8_t form);

	  virtual void beginPlayWav(uint32_t srate);
		virtual void endPlayWav();
    virtual void playWav(const char *fname) ;
    virtual bool isPlayingWav();
    virtual uint32_t duration();
    virtual uint32_t remaining();		
};	

#define ToneHAL ToneHalI2S_Zero	

#endif //Interface type

#else

#endif //microcontroler type

#endif
	
	


