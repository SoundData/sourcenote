#include "Tone.h"

Tone::Tone(unsigned short int startBeat) {
	startBeatPosition = (startBeat <= 32) ? startBeat : 0;
	// Invalid start beat is set to 0 and the tone will not be played
};

unsigned short int Tone::getStartBeatPosition(){
	return startBeatPosition;
}