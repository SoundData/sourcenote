#ifndef __PERCUSSIONTRACK_H_INCLUDED__
#define __PERCUSSIONTRACK_H_INCLUDED__

#include <unordered_map>
#include <vector>
#include "PercussionTone.h"

/* A Track contains a single Tone or collection of Tones.
 * It keeps Tones, that are played on the same channel, grouped together.
 * The purpose of a Track is for better organization and to have control over groups of Tones that are already playing.
 * An example is a melody, which consists of a group of NoteTones.
 *
 * PercussionTrack keeps track of only PercussionTones */

class PercussionTrack{
	public:
		PercussionTrack(std::vector<PercussionTone> toneList);
		std::unordered_map<unsigned short int, PercussionTone> tones;
		unsigned int repeatCount;
};

#endif 