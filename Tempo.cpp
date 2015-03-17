#include "Tempo.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

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
     sleep(60);
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
	double sampleInterval = (tempo->bpm/60);
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

	/******** Testing variables ********/

	double excess = 0;
	/* 'excess' accumulates the extra time used by 'sleep_for' that exceeds the 'sampleLength' time */
	int sleepCount = 0;
	/* 'sleepCount' counts all sleeps to find the average sleep time variation */
	double sleepTimeAccumulator = 0; 
	/* sum of all sleep times */
	std::cout<<"\n\n\n******  Time is measured in milliseconds  ****** \n";
	std::cout<<"\n******  Expected sleep length: " << sampleLength/1000 << "  ******\n\n\n";

	/************************************/

	while(tempo->isRunning){
		/* fetch tones */
		if(beatSubIntervalCount == beatSubInterval){
			/* On a beat, aka quarter note */
			//std::cout << "Beat " << beatCount << " BPM:" << tempo->bpm << "with time interval:" << (sampleInterval/1000000) << "\n" ;
			std::cout << "Average excess sleep time so far: " << ((sleepTimeAccumulator/sleepCount) - (sampleLength/1000)) << "\n";
			beatSubIntervalCount = 1;
			beatCount++;
			continue;
		}
		//std::cout << "*\n";
		beatSubIntervalCount++;

		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::microseconds(sampleLength));
		auto end = std::chrono::high_resolution_clock::now();
		sleepCount++;
		std::chrono::duration<double, std::milli> elapsed = end-start;
		excess += elapsed.count() - (sampleLength/1000);
		sleepTimeAccumulator += elapsed.count();


		std::cout<<"Sleep length: "<< elapsed.count() << "\t\tTotal excess: " << excess << "\t\tAverage sleep time: " << (sleepTimeAccumulator/sleepCount) <<'\n';

	}
	return NULL;
}


int main(){
	Tempo tempo = Tempo(120);
	tempo.start();
	return 0;
}

