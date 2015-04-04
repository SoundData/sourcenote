#include "Tempo.h"
#include "Tone.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

Tempo::Tempo(int beatsPerMinute) : bpm(beatsPerMinute) {};

void Tempo::start(){
	isRunning = true;

	pthread_t thread;
	int threadResult = pthread_create(&thread, NULL, &Tempo::run, this);
	
	if (threadResult){
		std::cout << "Error: Cannot create thread" << threadResult;
		exit(-1);
	}
	//sleep(30);
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
	double sampleLengthDouble = (tempo->bpm/60);  // beats per second 
	sampleLengthDouble = 1/sampleLengthDouble; // time length in seconds between "samples" (or fetches)
	sampleLengthDouble *= 1000000; // time length in microseconds between beats (quarter notes)
	sampleLengthDouble /= beatSubInterval; // time length in microseconds between subBeats
	int sampleLength = (int)sampleLengthDouble;

	int beatCount = 1;
	/* Similar to written music, beat 1 starts at time 0 and there is no beat 0. */
	int beatSubIntervalCount = 4;
	int count = 1;
	
	auto sampleLengthMicros = std::chrono::microseconds(sampleLength);
	auto beatZeroTime = std::chrono::high_resolution_clock::now();
	auto nextBeatTime = beatZeroTime + 1 * sampleLengthMicros;
	
	
	
	while(tempo->isRunning){
		/* fetch tones */
		if (std::chrono::high_resolution_clock::now() >= nextBeatTime){
			count++;
			if (beatSubIntervalCount == beatSubInterval){
				/* On a beat, aka quarter note */
				std::cout << "Beat " << beatCount << " BPM:" << tempo->bpm << "with time interval:" << (sampleLengthDouble/1000000) << "\n" ;
				beatSubIntervalCount = 1;
				beatCount++;
				nextBeatTime = beatZeroTime + count * sampleLengthMicros;
			}else{
				/* On a subBeat, aka 16th note */
				std::cout << "*\n";
				beatSubIntervalCount++;
				nextBeatTime = beatZeroTime + count * sampleLengthMicros;
			}
		}else{
			std::this_thread::yield();
			continue;
		}
	}
	return NULL;
}