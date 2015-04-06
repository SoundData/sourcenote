#include "NoteTrack.h"

NoteTrack::NoteTrack(std::vector<NoteTone> noteToneList){
	std::unordered_map<unsigned short int, NoteTone> toneMap;
	for (int i = 0; i < noteToneList.size(); i++){
		NoteTone tone = noteToneList[i];
		toneMap[tone.getStartBeatPosition()] = tone;
	}
	tones = toneMap;
}