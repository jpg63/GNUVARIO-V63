/****************************************************/
/*                                                  */
/*          Libraries ToneHal                       */
/*                                                  */
/*  version    Date     Description                 */
/*    1.0    20/01/19                               */
/*    1.1    26/01/19   petites modifications       */
/*                                                  */
/****************************************************/

#include "toneDAC_zero.h"
#include <Arduino.h>

#ifndef VARIO_SETTINGS_H
#endif

uint8_t  	waveForm = WAVEFORM_SINUS;
volatile	int 			sIndex; //Tracks sinewave points in array

volatile 	uint32_t 	elapsedBytes = 0;
File 			audioFile;

int 			*wavSamples; //array to store sinewave points
volatile 	uint32_t 	HeadIndex;
volatile	bool 			audioFileReady = false;
int 			sampleCount = 12; // Number of samples to read in block

void TC5_Handler();

/***********************************/
void ToneDacZero::setWaveForm(uint8_t form)
/***********************************/
{
#ifdef TONEDAC_DEBUG	
	SerialPort.print("Set form : ");
	SerialPort.println(form);
#endif TONEDAC_DEBUG

	waveForm = form;
	genForm(sampleCount);
#ifdef TONEDAC_DEBUG	
	SerialPort.println(waveForm);
#endif TONEDAC_DEBUG
}

//This function generates a sine wave and stores it in the wavSamples array
//The input argument is the number of points the sine wave is made up of
/***********************************/
void ToneDacZero::genForm(int sCount) {
/***********************************/
#ifdef TONEDAC_DEBUG	
	SerialPort.print("Gen Form : ");
	SerialPort.println(waveForm);
#endif TONEDAC_DEBUG
	
  switch(waveForm) {
		case WAVEFORM_SINUS:
#ifdef TONEDAC_DEBUG	
		  SerialPort.println("Wave form Sinus");
#endif TONEDAC_DEBUG
		  genSin(sCount);
			break;
			
		case WAVEFORM_TRIANGLE:
#ifdef TONEDAC_DEBUG	
		  SerialPort.println("Wave form Triangle");
#endif TONEDAC_DEBUG
		  genTriangle(sCount);
			break;
			
		case WAVEFORM_SQUARE:
#ifdef TONEDAC_DEBUG	
		  SerialPort.println("Wave form Square");
#endif TONEDAC_DEBUG
		  genSquare(sCount);
			break;
			
		default:
#ifdef TONEDAC_DEBUG	
		  SerialPort.println("Wave form dsefault");
#endif TONEDAC_DEBUG
		  genSin(sCount);
    break;
  }
}

/***********************************/
void ToneDacZero::genSin(int sCount) {
/***********************************/
  const float pi2 = 6.28; //2 x pi
  float in, amp; 
 
#ifdef TONEDAC_DEBUG	
  SerialPort.println("GenSin");
#endif TONEDAC_DEBUG

  amp = ((1023 * _tDAC_volume) / 100) / 2;

  for(int i=0; i<sCount;i++) { //loop to build sine wave based on sample count
    in = pi2*(1/(float)sCount)*(float)i; //calculate value in radians for sin()
    wavSamples[i] = ((int)(sin(in)*amp + amp)); //Calculate sine wave value and offset based on DAC resolution 511.5 = 1023/2
  }
}

/***********************************/
void ToneDacZero::genTriangle(int sCount) {
/***********************************/
  float pas;
  float in, amp; 

#ifdef TONEDAC_DEBUG	
	SerialPort.println("GenTriangle");
#endif TONEDAC_DEBUG

  amp = ((1023 * _tDAC_volume) / 100);
 
  pas = amp / (sCount/ 2);
#ifdef TONEDAC_DEBUG	
	SerialPort.print("Pas : ");
	SerialPort.println(pas);
#endif TONEDAC_DEBUG
	in = 0;

  for(int i=0; i<sCount;i++) { //loop to build sine wave based on sample count
#ifdef TONEDAC_DEBUG	
	  SerialPort.print("WaveSample : ");
		SerialPort.println(in);
#endif TONEDAC_DEBUG
    wavSamples[i] = (int)in;
    if (i < (int)(sCount/2))
      in += pas;
    else 
		  in -= pas;
  }
}

/***********************************/
void ToneDacZero::genSquare(int sCount) {
/***********************************/
 float in, amp; 
 
#ifdef TONEDAC_DEBUG	
 SerialPort.println("GenSquare");
#endif TONEDAC_DEBUG
 amp = ((1023 * _tDAC_volume) / 100);

 for(int i=0; i<sCount;i++) { //loop to build sine wave based on sample count
  if (i < (int)(sCount/2))
    wavSamples[i] = ((int)amp); 
	else 
		wavSamples[i] = 0;
 }
}

//Function that is used to check if TC5 is done syncing
//returns true when it is done syncing
/***********************************/
bool ToneDacZero::tcIsSyncing()
/***********************************/
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}

//Reset TC5 
/***********************************/
void ToneDacZero::tcReset()
/***********************************/
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}

//disable TC5
/***********************************/
void ToneDacZero::tcDisable()
/***********************************/
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}

// Configures the TC to generate output events at the sample frequency.
//Configures the TC in Frequency Generation mode, with an event output once
//each time the audio sample frequency period expires.
/***********************************/
void ToneDacZero::tcConfigure(int sampleRate)
/***********************************/
{
 // Enable GCLK for TCC2 and TC5 (timer counter input clock)
 GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
 while (GCLK->STATUS.bit.SYNCBUSY);

  tcReset(); //reset TC5

  // Set Timer counter Mode to 16 bits
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
 // Set TC5 mode as match frequency
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
 //set prescaler and enable TC5
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_ENABLE;
 //set TC5 timer counter based off of the system clock and the user defined sample rate or waveform
 TC5->COUNT16.CC[0].reg = (uint16_t) (SystemCoreClock / sampleRate - 1);
 while (tcIsSyncing());
 
 // Configure interrupt request
 NVIC_DisableIRQ(TC5_IRQn);
 NVIC_ClearPendingIRQ(TC5_IRQn);
 NVIC_SetPriority(TC5_IRQn, 0);
 NVIC_EnableIRQ(TC5_IRQn);

  // Enable the TC5 interrupt request
 TC5->COUNT16.INTENSET.bit.MC0 = 1;
 while (tcIsSyncing()); //wait until TC5 is done syncing 
} 


//This function enables TC5 and waits for it to be ready
/***********************************/
void ToneDacZero::tcStartCounter()
/***********************************/
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
  while (tcIsSyncing()); //wait until snyc'd
}

/***********************************/
void TC5_Handler (void)
/***********************************/
{
	if (waveForm != WAVEFORM_WAV) { 
		analogWrite(A0, wavSamples[sIndex]);
		if (sIndex==sampleCount-1)
			{
				sIndex = 0;	
/*     toneDAC.tcDisable();
     toneDAC.tcReset();
	   toneDAC.tcConfigure(toneDAC.sampleRate); //setup the timer counter based off of the user entered sample rate
//start timer, once timer is done interrupt will occur and DAC value will be updated
     toneDAC.tcStartCounter(); */
			}
		else
			{		
				sIndex++;
				TC5->COUNT16.INTFLAG.bit.MC0 = 1;
			}
	}
	else {
		 if (audioFile.available()) {
        
        
        uint32_t current_SampleIndex = sIndex;
            
        if (current_SampleIndex > HeadIndex) {
          audioFile.read(&wavSamples[HeadIndex], current_SampleIndex - HeadIndex);
          HeadIndex = current_SampleIndex;
        }
        else if (current_SampleIndex < HeadIndex) {
          audioFile.read(&wavSamples[HeadIndex],SAMPLECOUNT-1 - HeadIndex);
          audioFile.read(wavSamples, current_SampleIndex);
          HeadIndex = current_SampleIndex;
        }
        
        
        if (sIndex < SAMPLECOUNT - 1)
        {
          analogWrite(A0, wavSamples[sIndex++]);
          elapsedBytes++;
            // Clear the interrupt
            //TC5->COUNT16.INTFLAG.bit.MC0 = 1;
        }
        else
        {
          sIndex = 0;
            //TC5->COUNT16.INTFLAG.bit.MC0 = 1;
        }
		 }
		 else if (audioFileReady) {
       audioFile.close();
       audioFileReady = false;
       elapsedBytes=0;
        //tc reset
        //TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
        //while (TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY);
        //while (TC5->COUNT16.CTRLA.bit.SWRST);
    
        //tc disable
       TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
       while (TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY);
        
       analogWrite(A0, 512);
     }
	}
}


/***********************************/
void ToneDacZero::init(void) {
/***********************************/
  analogWriteResolution(10); //set the Arduino DAC for 10 bits of resolution (max)
	analogWrite(A0, 0);

  _tDAC_volume = 100;
	waveForm = WAVEFORM_SINUS;
  
  /*Allocate the buffer where the samples are stored*/
//  wavSamples = (int *) malloc(sampleCount * sizeof(int));
//  genForm(sampleCount); //function generates sine wave
  wavSamples = (int *) malloc(SAMPLECOUNT * sizeof(int));
	genForm(SAMPLECOUNT); //function generates sine wave
}

/***********************************/
void ToneDacZero::begin(uint32_t srate) {
/***********************************/
	audioFileReady = false;
  sampleRate = srate;
	waveForm = WAVEFORM_WAV;
  sIndex = 0;   //Set to zero to start from beginning of waveform
	
	/*Modules configuration */
  analogWriteResolution(10); //set the Arduino DAC for 10 bits of resolution (max)
	analogWrite(A0, 0);

	tcConfigure(srate);
}

/***********************************/
void ToneDacZero::tone(unsigned long frequency
/***********************************/
#ifdef TONEDAC_VOLUME
            , uint8_t volume
#endif
#ifdef TONEDAC_LENGTH
            , unsigned long length, uint8_t background
#endif
	    ) {

  uint32_t tmpSampleCount; 			
  /* check if no tone */ 
  if (toneDACMuted || frequency == 0
#ifdef TONEDAC_VOLUME     
      || volume == 0
#endif
      ) { noTone(); return; } 

  /* check volume */
#ifdef TONEDAC_VOLUME
  if (volume > 100) volume = 100;
	if (_tDAC_volume != volume) 
	  {
	    _tDAC_volume = volume;
		}
#endif

  if (frequency > 10000) frequency = 10000;
	_frequency = frequency;
  tmpSampleCount = SAMPLERATE / frequency;
	multiplicateur = 1;
	while (tmpSampleCount > SAMPLECOUNT) {
		tmpSampleCount /= 2;
		multiplicateur *= 2;
	}

#ifdef TONEDAC_DEBUG	
  SerialPort.print("Multiplicateur : ");
	SerialPort.println(multiplicateur);
  SerialPort.print("SampleRate : ");
	SerialPort.println(tmpSampleCount);
#endif TONEDAC_DEBUG
	
  sIndex = 0;   //Set to zero to start from beginning of waveform
	sampleRate = SAMPLERATE / multiplicateur; 
	if (sampleRate > 120000) sampleRate = 120000;
	sampleCount = tmpSampleCount;
	
	genForm(sampleCount);	
  tcConfigure(sampleRate); //setup the timer counter based off of the user entered sample rate
/*  //loop until all the sine wave points have been played
  while (sIndex<sampleCount)
  { 
 //start timer, once timer is done interrupt will occur and DAC value will be updated
    tcStartCounter(); 
  }
  //disable and reset timer counter
  tcDisable();
  tcReset();*/
  
	tcStartCounter(); 	
	
  /* compute length time */
#ifdef TONEDAC_LENGTH
  if (length > 0 && background) {  // Background tone playing, returns control to your sketch.

    _tDAC_time = millis() + length; // Set when the note should end.
    //TODO !!!                     // Activate the timer interrupt.
  }

  if (length > 0 && !background) { delay(length); noToneDAC(); } // Just a simple delay, doesn't return control untill finished.
#endif
}

/***********************************/
void ToneDacZero::noTone() {
/***********************************/
#ifdef TONEDAC_LENGTH
  //TODO !!!!                     // Remove the timer interrupt.
#endif

//  digitalWrite(LED3,false);
  analogWrite(A0, 0);
  tcDisable();
  tcReset();
}

#ifdef TONEDAC_LENGTH
// TODO !!! { // Timer interrupt vector.
//  if (millis() >= _tAC_time) noToneAC(); // Check to see if it's time for the note to end.
//}
#endif

/***********************************/
void ToneDacZero::toneMute(bool newMuteState) {
/***********************************/
  /* stop tone if needed */
  if( newMuteState ) {
    noTone();
  }

  /* save */
  toneDACMuted = newMuteState;
}

/***********************************/
void ToneDacZero::end() {
/***********************************/
	tcDisable();
	tcReset();
	analogWrite(A0, 0);
    
}

/***********************************/
void ToneDacZero::play(const char *fname) {
/***********************************/
  if(audioFileReady) audioFile.close();
  
	audioFile = SD.open(fname);
  fileSize = audioFile.size();
    
  if(!audioFile){
    end();
    return;
  }
    
  for(int i =0; i<44; i++) audioFile.read();
    
  audioFile.read(wavSamples, SAMPLECOUNT);
  HeadIndex = 0;
    
    /*once the buffer is filled for the first time the counter can be started*/
  tcStartCounter();
    
  audioFileReady = true;
    
}

/***********************************/
uint32_t ToneDacZero::duration()
/***********************************/
{
  if(audioFileReady)  return (fileSize/sampleRate);
  return 0;
}

/***********************************/
uint32_t ToneDacZero::remaining()
/***********************************/
{
  if(audioFileReady) return ((fileSize-elapsedBytes)/sampleRate);
  return 0;
}


/***********************************/
bool ToneDacZero::isPlaying()
/***********************************/
{
  return audioFileReady;
}

