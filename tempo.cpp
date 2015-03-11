#include "tempo.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

void Tempo::start(){
	isRunning = true;
	bpm = 120;

	pthread_t thread;
	int threadResult = pthread_create(&thread, NULL, 
                          &Tempo::run, this);
     if (threadResult){
     	std::cout << "Error: Cannot create thread" << threadResult;
     	exit(-1);
      }
     //sleep(60);
}

void* Tempo::run(void*temp){
	int beatSubInterval = 4;
	/* 'beatSubInterval' defines how many times we fetch new tones between every quarter beat.
	 * If its equal to 4, we fetch every 16th note in a measure. For 1, that would be only once per beat. 2 would be for 8th notes,
	 * which is 2 tmes per beat */
	Tempo *tempo = (Tempo*)temp;
	/* Translate BMP to microseconds between beats */
	float sampleInterval = (tempo->bpm/60);
	/* sampleInterval = beats per second */
	sampleInterval = 1/sampleInterval;
	/* sampleInterval = sleep length in seconds between samples */
	sampleInterval *= 1000000;
	/* sampleInterval = sleep length in microseconds between samples */
	sampleInterval /= beatSubInterval;
	/* sampleInterval = sleep length in microseconds between subBeats */
	int sampleLength = (int)sampleInterval;

	int beatCount = 1;
	int beatSubIntervalCount = 4;

	while(tempo->isRunning){
		/* fetch tones */
		if(beatSubIntervalCount == beatSubInterval){
			/* On a beat, aka quarter note */
			std::cout << "Beat " << beatCount << " BPM:" << tempo->bpm << "\n" ;
			beatSubIntervalCount = 1;
			beatCount++;
			continue;
		}
		std::cout << "*\n";
		beatSubIntervalCount++;
		usleep(sampleLength);
	}
	return NULL;
}

/*
int main(){
	Tempo tempo;
	tempo.start();
	return 0;
}
*/
