#include "ToneCreator.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <string>

std::string fileNames[] = {"clap.wav", "snare.wav", "kick.wav", "chat.wav", "cowbell.wav", "cymbal.wav", "hconga.wav", "htom.wav", 
"lconga.wav", "ltom.wav", "mconga.wav", "ohat.wav"};

//ToneCreator::ToneCreator(std::vector<GameMessage> initialParameters) : intialParameters(intialParameters)
ToneCreator::ToneCreator(){
	initializeNoteData();
	srand(time(NULL));
}

void ToneCreator::initializeNoteData(){
	/* Current version of Clang on Yosemite doesn't support C++ initializer lists!
	 * keyNotes["C"] = {"C", "D", "E", "F", "G", "A", "B"}; -- Will not compile... */
	this->noteFrequencies["Ab1"] = 207.65;
	this->noteFrequencies["A1"] = 220.0;
	this->noteFrequencies["A#1"] = 233.08;
	this->noteFrequencies["Bb1"] = 233.08;
	this->noteFrequencies["B1"] = 246.94;
	this->noteFrequencies["C1"] = 261.63;
	this->noteFrequencies["C#1"] = 277.18;
	this->noteFrequencies["Dd1"] = 277.18;
	this->noteFrequencies["D1"] = 293.66;
	this->noteFrequencies["D#1"] = 311.13;
	this->noteFrequencies["Eb1"] = 311.13;
	this->noteFrequencies["E1"] = 329.63;
	this->noteFrequencies["F1"] = 349.23;
	this->noteFrequencies["F#1"] = 369.99;
	this->noteFrequencies["G1"] = 369.99;
	this->noteFrequencies["G#1"] = 415.30;

	this->noteFrequencies["Ab2"] = 415.30;
	this->noteFrequencies["A2"] = 440.00;
	this->noteFrequencies["A#2"] = 466.16;
	this->noteFrequencies["Bb2"] = 466.16;
	this->noteFrequencies["B2"] = 493.88;
	this->noteFrequencies["C2"] = 523.25;
	this->noteFrequencies["C#2"] = 554.37;
	this->noteFrequencies["Dd2"] = 554.37;
	this->noteFrequencies["D2"] = 587.33;
	this->noteFrequencies["D#2"] = 622.25;
	this->noteFrequencies["Eb2"] = 622.25;
	this->noteFrequencies["E2"] = 659.25;
	this->noteFrequencies["F2"] = 698.46;
	this->noteFrequencies["F#2"] = 739.99;
	this->noteFrequencies["G2"] = 783.99;
	this->noteFrequencies["G#2"] = 830.61;

	std::vector<std::string> cNotes;
	cNotes.push_back("C");
	cNotes.push_back("D");
	cNotes.push_back("E");
	cNotes.push_back("F");
	cNotes.push_back("G");
	cNotes.push_back("A");
	cNotes.push_back("B");
	keyNotes["C"] = cNotes;
	this->allKeys.push_back("C");


	std::vector<std::string> dNotes;
	dNotes.push_back("D");
	dNotes.push_back("E");
	dNotes.push_back("F#");
	dNotes.push_back("G");
	dNotes.push_back("A");
	dNotes.push_back("B");
	dNotes.push_back("C#");
	keyNotes["D"] = dNotes;
	this->allKeys.push_back("D");

	std::vector<std::string> gNotes;
	gNotes.push_back("G");
	gNotes.push_back("A");
	gNotes.push_back("B");
	gNotes.push_back("C");
	gNotes.push_back("D");
	gNotes.push_back("E");
	gNotes.push_back("F#");
	keyNotes["G"] = gNotes;
	this->allKeys.push_back("G");

	std::vector<std::string> aNotes;
	aNotes.push_back("A");
	aNotes.push_back("B");
	aNotes.push_back("C#");
	aNotes.push_back("D");
	aNotes.push_back("E");
	aNotes.push_back("F#");
	aNotes.push_back("G#");
	keyNotes["A"] = aNotes;
	this->allKeys.push_back("A");

	std::vector<std::string> eNotes;
	eNotes.push_back("E");
	eNotes.push_back("F#");
	eNotes.push_back("G#");
	eNotes.push_back("A");
	eNotes.push_back("B");
	eNotes.push_back("C#");
	eNotes.push_back("D#");
	keyNotes["E"] = eNotes;
	this->allKeys.push_back("E");

	fileNames[kSnare] = "snare.wav";
	fileNames[kKick] = "kick.wav";
	fileNames[kClap] = "clap.wav";

}

NoteTone ToneCreator::makeToneWithNote(std::string note){
	note += "1"; //In octave 1
	return NoteTone(1,5, kSine, noteFrequencies.at(note));
}

NoteTone ToneCreator::makeRandomNoteInKeyAndOctave(std::string key, unsigned short int octave){
	currentKey = key;
	std::vector<std::string> notesInKey = keyNotes[key];
	int randomNoteInKeyIndex = rand() % notesInKey.size();
	std::cout << notesInKey.size() << " random: " << randomNoteInKeyIndex << "\n";
	std::string randomNote = notesInKey[randomNoteInKeyIndex];
	randomNote += ('0' + octave);
	return NoteTone(1,2,kSine,noteFrequencies[randomNote]);
}

NoteTone ToneCreator::makeRandomNoteInTimeFrameAndKeyAndOctave(unsigned short int startTime, unsigned short int endTime, std::string key, unsigned short int octave){
	//The startBeat and endBeat of the note can be on, or between, startTime and endTime 
	std::vector<std::string> notesInKey = keyNotes[key];
	int randomNoteIndex = rand() % notesInKey.size();
	std::string randomNote = notesInKey[randomNoteIndex];
	randomNote += ('0' + octave);
	int startBeat = rand() % endTime + 1;
	//For now, every note will be a 16th note long. So the endBeat will be startBeat+1
	std::cout << "Random melody note: " << randomNote << " on beat:" << startBeat << "\n";
	return NoteTone(startBeat,startBeat+1,kSine,noteFrequencies[randomNote]);
}

NoteTrack ToneCreator::makeRandomMelodyNotesInKeyAndOctave(std::string key, unsigned short int octave){
	//For now, a melody will consist of 15 - 20 notes, 2 measures in length 
	int randomNumberOfNotes = rand() % 6 + 15;
	std::vector<NoteTone> notes;
	currentKey = key;

	for (int i = 0; i < randomNumberOfNotes; i++){
		NoteTone newNote = makeRandomNoteInTimeFrameAndKeyAndOctave(1,32,"C", 1);
		notes.push_back(newNote);
	}
	return NoteTrack(notes);
}

NoteTrack ToneCreator::makeRandomMelodyNotesInRandomKeyAndRandomOctave(){
	//For now, a melody will consist of 15 - 20 notes, 2 measures in length 
	int randomNumberOfNotes = rand() % 6 + 15;
	std::vector<NoteTone> notes;
	std::string randomKey = allKeys[rand() % allKeys.size()];
	currentKey = randomKey;
	int randomOctave = rand() % 2 + 1;
	std::cout << "Random melody in key:" << randomKey << " and octave:" << randomOctave << "\n";
	for (int i = 0; i < randomNumberOfNotes; i++){
		NoteTone newNote = makeRandomNoteInTimeFrameAndKeyAndOctave(1,32,randomKey, randomOctave);
		notes.push_back(newNote);
	}
	return NoteTrack(notes);
}


PercussionTrack ToneCreator::makePercussionTrackWithTypeAndBeats(PercussionToneType type, std::vector<unsigned short int> beats){
	std::cout << "Generating " << beats.size() << " beats\n";
	std::vector<PercussionTone> percussions;
	for(int i = 0; i < beats.size(); i++){
		percussions.push_back(PercussionTone(beats[i], fileNames[type]));
		PercussionTone tone = percussions[i];
		std::cout << "PercussionTone: " << tone.getStartBeatPosition() << " " << tone.getFileName() << "\n";
	}
	std::cout << "\n";
	return PercussionTrack(percussions);
}

PercussionTrack ToneCreator::makeRandomBeatWithPercussionType(PercussionToneType type){
	/* chooses randomly between half notes, quarter notes, or 8th notes. */
	int random = rand() % 3;
	std::vector<PercussionTone> percussions;
	std::string fileName = fileNames[type];
	switch (random){
		case 0:{
			/* half notes, aka every other quarter note */
			/* choose randomly between starting on beat 1 or 2 */
			std::cout << "Generating half notes, ";
			int randomStartBeat = rand() % 2;
			if(randomStartBeat == 1){
				std::cout << "starting on beat 1\n";
			}else{
				std::cout << "starting on beat 2\n";
			}
			for (int i = 1; i <= 32; i++){
				if(randomStartBeat == 1){
					/* start on beat 1 */
					if(((i - 1) % 2) == 0){
						PercussionTone tone = PercussionTone(i, fileName);
						percussions.push_back(tone);
					}
				}else{
					/* start on beat 2 */
					if((i % 2) == 0){
						PercussionTone tone = PercussionTone(i, fileName);
						percussions.push_back(tone);
					}
				}
			}
			break;
		}

		case 1:{
			/* quarter notes */
			std::cout << "Generating quarter notes\n";
			for (int i = 1; i <= 32; i++){
				if(((i - 1) % 4) == 0){
					PercussionTone tone = PercussionTone(i, fileName);
					percussions.push_back(tone);
				}
			}
			break;
		}

		case 2:{
			/* 8th notes, aka every half quarter note */
			std::cout << "Generating 8th notes\n";
			for (int i = 1; i <= 32; i++){
				if(((i - 1) % 2) == 0){
					PercussionTone tone = PercussionTone(i, fileName);
					percussions.push_back(tone);
				}
			}
			break;
		}
	}
	std::cout << "\n";
	return PercussionTrack(percussions);

}


/*
int main(){
	ToneCreator tc = ToneCreator();
	*/

	/***** Uncomment to try note functions *********
	NoteTrack melody = tc.makeRandomMelodyNotesInKeyAndOctave("C", 1);
	std::cout << "Above melody includes " << melody.tones.size() << " notes\n\n";

	NoteTrack melody2 = tc.makeRandomMelodyNotesInRandomKeyAndRandomOctave();
	std::cout << "Above melody includes " << melody2.tones.size() << " notes\n\n";
	***************/


	/***** Uncomment to try percussion functions ****
	std::vector<unsigned short int> beats;
	beats.push_back(1);
	beats.push_back(2);
	beats.push_back(3);
	beats.push_back(4);
	beats.push_back(5);

	PercussionTrack track1 = tc.makePercussionTrackWithTypeAndBeats(kClap, beats);
	PercussionTrack track2 = tc.makeRandomBeatWithPercussionType(kKick);
	**************/

/*
	return 0;
}
*/
