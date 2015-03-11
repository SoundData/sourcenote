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
     	std::cout << "Error: Cannot create thread" << rc;
     	exit(-1);
      }
     //sleep(60);
}

void* Tempo::run(void*temp){
	int count = 0;
	Tempo *tempo = (Tempo*)temp;
	/* Translate BMP to microseconds between beats */
	float sampleInterval = (tempo->bpm/60);
	/* sampleInterval = beats per second */
	sampleInterval = 1/sampleInterval;
	/* sampleInterval = sleep length in seconds between samples */
	sampleInterval *= 1000000;
	/* sampleInterval = sleep length in microseconds between samples */
	int sampleLength = (int)sampleInterval;
	while(tempo->isRunning){
		/* fetch tones */
		std::cout << "Beat " << count << " BPM:" << tempo->bpm << "\n" ;
		count++;
		usleep(sampleLength);
	}
}

/*
int main(){
	Tempo tempo;
	tempo.start();
}
*/