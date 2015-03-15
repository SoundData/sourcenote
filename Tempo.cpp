#include "Tempo.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

Tempo::Tempo(int beatsPerMinute) : bpm(beatsPerMinute) {};

void Tempo::start(){
	isRunning = true;

	pthread_t thread;
	int threadResult = pthread_create(&thread, NULL, 
                          &Tempo::run, this);
     if (threadResult){
     	std::cout << "Error: Cannot create thread" << threadResult;
     	exit(-1);
      }
     //sleep(60);
}

void Tempo::stop(){
	isRunning = false;
}

void* Tempo::run(void*temp){
	int beatSubInterval = 4;
	/* 'beatSubInterval' defines how many times we fetch new tones between every quarter beat.
	 * If its equal to 4, we fetch every 16th note in a measure. 1 would be only once per beat. 2 would be twice per beat
	 * which would be 8th notes */
	Tempo *tempo = (Tempo*)temp;

	/* Translate BPM to microseconds between subBeats */
	float sampleInterval = (tempo->bpm/60);
	/* sampleInterval = beats per second */
	sampleInterval = 1/sampleInterval;
	/* sampleInterval = time length in seconds between "samples" (or fetches) */
	sampleInterval *= 1000000;
	/* sampleInterval = time length in microseconds between beats (quarter notes) */
	sampleInterval /= beatSubInterval;
	/* sampleInterval = time length in microseconds between subBeats */
	int sampleLength = (int)sampleInterval;

	int beatCount = 1;
	/* Similar to written music, beat 1 starts at time 0 and there is no beat 0. */
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
	Tempo tempo = Tempo(120);
	tempo.start();
	return 0;
}
*/
