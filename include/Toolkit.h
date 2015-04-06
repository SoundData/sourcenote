#ifndef TOOLKIT_H
#define TOOLKIT_H

// std lib
#include <iostream>
#include <string>

// stk
#include "RtAudio.h"
#include "Voicer.h"
#include "SineWave.h"
#include "BlitSaw.h"
#include "Noise.h"
#include "Voicer.h"

// our stuff
#include "NoteTone.h"
#include "PercussionTone.h"

class Toolkit {	
	private:
		RtAudio dac;
		unsigned int now;
		
	public:
		Toolkit(void);
		~Toolkit(void);
		int startStream(void);
		int stopStream(void);
		void playTone(unsigned int start, int duration, std::string waveform, float freq);
		static int mainTick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer);
		void playNoteTone(NoteTone *t);
		void playPercussionTone(PercussionTone *t);
};

#endif