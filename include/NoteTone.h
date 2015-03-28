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
		unsigned short int endBeatPosition;
		/* Must be an int from 1 to 32. EndBeatPosition is the beat position where the tone will be played in a 2 measure interval.
		 * Measures are always in 4/4 time with each measure containing 16 beats, making 2 measures contain 32 beats. */
		WaveForm waveform;
		float frequency;

	public:
		NoteTone(unsigned short int endBeat, unsigned short int startBeat, WaveForm waveform, float frequency);
		unsigned short int getEndBeatPosition();
		WaveForm getWaveform();
		float getFrequency();
};

#endif 