#include "NoteTone.h"

NoteTone::NoteTone(unsigned int startTime, unsigned int endTime, WaveForm waveform, int frequency) : Tone(startTime), endTime(endTime), waveform(waveform), frequency(frequency) {};

unsigned int NoteTone::getEndTime(){
	return endTime;
}

WaveForm NoteTone::getWaveform(){
	return waveform;
}

int NoteTone::getFrequency(){
	return frequency;
}