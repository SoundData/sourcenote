#ifndef __NOTETONE_H_INCLUDED__
#define __NOTETONE_H_INCLUDED__

#include "Tone.h"

enum WaveForm{
	kSine = 0,
	kSquare,
	kTraingle,
	kSawtooth,
};

class NoteTone: public Tone{
	private:
		unsigned int endTime;
		WaveForm waveform;
		int frequency;

	public:
		NoteTone(unsigned int startTime, unsigned int endTime, WaveForm waveform, int frequency);
		unsigned int getEndTime();
		WaveForm getWaveform();
		int getFrequency();
};

#endif 