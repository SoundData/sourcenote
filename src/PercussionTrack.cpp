#include "PercussionTrack.h"

PercussionTrack::PercussionTrack(std::vector<PercussionTone> percussionToneList){
	std::unordered_map<unsigned short int, PercussionTone> toneMap;
	for (int i = 0; i < percussionToneList.size(); i++){
		PercussionTone tone = percussionToneList[i];
		toneMap[tone.getStartBeatPosition()] = tone;
	}
	tones = toneMap;
}