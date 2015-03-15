#include "Tone.h"

Tone::Tone(int startTime) : startTime(startTime) {};

unsigned int Tone::getStartTime(){
	return startTime;
}