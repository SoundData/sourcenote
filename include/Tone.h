#ifndef __TONE_H_INCLUDED__
#define __TONE_H_INCLUDED__

class Tone{
	private:
		unsigned int startTime;
		unsigned short int startBeatPosition; 
		/* Must be an int from 1 to 32. StartBeatPosition is the beat position where the tone will be played in a 2 measure interval.
		 * Measures are always in 4/4 time with each measure containing 16 beats, making 2 measures contain 32 beats. */

	public:
		Tone(unsigned short int startBeat);
		Tone(){}; //Required to access a Tone in a vector of Tones. My research suggests its a Clang specific issue.
		unsigned short int getStartBeatPosition();
};

#endif 