#ifndef __TONECREATOR_H_INCLUDED__
#define __TONECREATOR_H_INCLUDED__

#include "Tone.h"
#include "NoteTone.h"
#include <unordered_map>
#include <vector>
#include <iostream>

/* A ToneCreator object should be instantiated with a vector of GameMessages 
 * containing the intial parameters of the game (level, charcter, etc.).
 * Initial parameters are necessary to create a relevant, initial melody. */

class ToneCreator{
	private:
		std::unordered_map<std::string, float> noteFrequencies;
		/* Map keys are in the format of "<Note letter A-G><#,d,or nothing><1,2,or 3>"
		 * Examples:
		 * "A#1" - 'A' sharp first octave
		 * "C1" - 'C' first octave
		 * "Bb2" - 'B' flat octave 2
		 * "Ab3" - 'A' flat octave 3 */
		std::unordered_map< std::string, std::vector <std::string> > keyNotes;
		std::string currentKey;
		std::vector <std::string> allKeys;
		void initializeNoteData();

	public:
		//Tempo(std::vector<GameMessage> initialParameters);
		//Tone* makeTonesForEvent(GameMessage event);
		ToneCreator();
		NoteTone makeToneWithNote(std::string note);
		NoteTone makeRandomNoteInKeyAndOctave(std::string key, unsigned short int octave);
		/* There are 3 octaves, so the octave should be a number from 1 to 3.
		 * Examples of key: "C", "A", "D" */
		NoteTone makeRandomNoteInTimeFrameAndKeyAndOctave(unsigned short int startTime, unsigned short int endTime, std::string key, unsigned short int octave);
		/* StartTime and endTime should be a 16th note beat within a 2 measure interval, so between 1 and 32. */
		std::vector<NoteTone> makeRandomMelodyNotesInKeyAndOctave(std::string key, unsigned short int octave);
		std::vector<NoteTone> makeRandomMelodyNotesInRandomKeyAndRandomOctave();
};

#endif