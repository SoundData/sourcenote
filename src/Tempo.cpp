#include "Tempo.h"
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
	sleep(30);
}

void Tempo::stop(){
	isRunning = false;
}

void Tempo::addNoteTones(std::vector<NoteTone> tones){
	NoteTrack track = NoteTrack(tones);
	noteTracks.push_back(track);
}

void Tempo::addPercussionTones(std::vector<PercussionTone> tones){
	PercussionTrack track = PercussionTrack(tones);
	percussionTracks.push_back(track);
}

void* Tempo::run(void*temp){
	unsigned short int beatsInAQuarterNote = 4;
	/* 'beatsInAQuarterNote' defines how many times we fetch new tones between every quarter note.
	 * If equal to 4, a single measure will have 16 beats (4 quater notes with each having 4 16th notes)
	 * If its equal to 4, we fetch every 16th note in a measure (fetch 16 times per measure).
	 * 1 would be only once per quarter note (fetch 4 times a measure).
	 * 2 would be twice per beat which would be 8th notes (fetch 8 times per measure) */
	Tempo *tempo = (Tempo*)temp;
	double sampleLengthDouble = (tempo->bpm/60);  // beats per second 
	sampleLengthDouble = 1/sampleLengthDouble; // time length in seconds between "samples" (or fetches)
	sampleLengthDouble *= 1000000; // time length in microseconds between beats (quarter notes)
	sampleLengthDouble /= beatsInAQuarterNote; // time length in microseconds between subBeats
	int sampleLength = (int)sampleLengthDouble;

	unsigned int totalBeatsProduced = 1; // total number of subBeats produced ( Assuming beatsInAQuarterNote == 4, 32 for every 2 measures, 4 per beat).
	unsigned short int currentBeatPosition = 1; // gives the current subBeat position in the standard two measure interval (loops from 1 to 32 when beatsInAQuarterNote = 4)
	/* Similar to written music, beat 1 starts at time 0 and there is no beat 0. */

	auto sampleLengthMicros = std::chrono::microseconds(sampleLength);
	auto beatZeroTime = std::chrono::high_resolution_clock::now();
	auto nextBeatTime = beatZeroTime + 1 * sampleLengthMicros;

	while(tempo->isRunning){
		if (std::chrono::high_resolution_clock::now() >= nextBeatTime){
			totalBeatsProduced++;
			if(currentBeatPosition == (beatsInAQuarterNote*8)+1){ // 8 is how many quarter notes are in a 2 meaures
				currentBeatPosition = 1;
			}
			/* On a beat (Or 16th note assuming beatsInAQuarterNote == 4) */
			std::cout << "* ";
			if((currentBeatPosition-1)%beatsInAQuarterNote == 0){
				std::cout << "Quarter " << totalBeatsProduced/beatsInAQuarterNote << "\n";
			}else{
				std::cout << "\n";
			}
			nextBeatTime = beatZeroTime + totalBeatsProduced * sampleLengthMicros;

			/* Get all notes for the current beat */
			std::vector<NoteTone> notesForBeat = tempo->getNoteTonesForBeatPosition(currentBeatPosition);
			std::vector<PercussionTone> percussionsForBeat = tempo->getPercussionTonesForBeatPosition(currentBeatPosition);

			for (int i=0;i<notesForBeat.size();i++){
				NoteTone note = notesForBeat[i];
				/* Send to STK! */
				//std::cout << "\n" << note.getFrequency() << "\n\n";
			}

			for (int i=0;i<percussionsForBeat.size();i++){
				PercussionTone percussion = percussionsForBeat[i];
				/* Send to STK! */
				//std::cout << "\n" << percussion.getFileName() << "\n\n";
			}
			currentBeatPosition++;
		}else{
			std::this_thread::yield();
			continue;
		}
	}
	return NULL;
}

std::vector<NoteTone> Tempo::getNoteTonesForBeatPosition(unsigned short int beatPosition){
	std::vector<NoteTone> notesForBeat;
	for(int i = 0; i < noteTracks.size(); i++){
		NoteTrack track = noteTracks[i];
		if(track.tones.count(beatPosition) == 0){
			/* checks if the track does not have a note for the beatPosition */
			continue;
		}
		notesForBeat.push_back(track.tones[beatPosition]);
		track.repeatCount--;
		if(track.repeatCount == -1){
			noteTracks.erase(noteTracks.begin() + i);
		}
	}
	return notesForBeat;
}

std::vector<PercussionTone> Tempo::getPercussionTonesForBeatPosition(unsigned short int beatPosition){
	std::vector<PercussionTone> percussionsForBeat;
	for(int i = 0; i < percussionTracks.size(); i++){
		PercussionTrack track = percussionTracks[i];
		percussionsForBeat.push_back(track.tones[beatPosition]);
		track.repeatCount--;
		if(track.repeatCount == -1){
			percussionTracks.erase(percussionTracks.begin() + i);
		}
	}
	return percussionsForBeat;

}

/*
int main(){
	Tempo t = Tempo(120);
	std::vector<NoteTone> nv;
	nv.push_back(NoteTone(1,2,kSine,10.0));
	nv.push_back(NoteTone(10,11,kSine,2.0));
	nv.push_back(NoteTone(15,16,kSine,3.0));
	nv.push_back(NoteTone(16,17,kSine,4.0));
	nv.push_back(NoteTone(18,19,kSine,5.0));
	nv.push_back(NoteTone(20,21,kSine,6.0));
	nv.push_back(NoteTone(21,22,kSine,7.0));
	nv.push_back(NoteTone(22,23,kSine,8.0));
	nv.push_back(NoteTone(27,28,kSine,8.0));
	nv.push_back(NoteTone(28,29,kSine,8.0));
	nv.push_back(NoteTone(32,33,kSine,8.0));

	t.addNoteTones(nv);

	std::vector<PercussionTone> pv;
	pv.push_back(PercussionTone(5,"hi.wav"));
	pv.push_back(PercussionTone(6,"hi.wav"));
	pv.push_back(PercussionTone(7,"hi.wav"));
	pv.push_back(PercussionTone(15,"hi.wav"));
	pv.push_back(PercussionTone(16,"hi.wav"));
	pv.push_back(PercussionTone(25,"hi.wav"));
	pv.push_back(PercussionTone(26,"hi.wav"));
	pv.push_back(PercussionTone(27,"hi.wav"));
	pv.push_back(PercussionTone(28,"hi.wav"));
	//NoteTone tone = NoteTone(5,6,kSine, 100.0f);
	t.start();

	return 0;
}
*/