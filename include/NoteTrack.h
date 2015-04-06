#ifndef __NOTETRACK_H_INCLUDED__
#define __NOTETRACK_H_INCLUDED__

#include <unordered_map>
#include <vector>
#include "NoteTone.h"

/* A Track contains a single Tone or collection of Tones.
 * It keeps Tones, that are played on the same channel, grouped together.
 * The purpose of a Track is for better organization and to have control over groups of Tones that are already playing.
 * An example is a melody, which consists of a group of NoteTones.
 *
 * NoteTrack keeps track of only NoteTones */

class NoteTrack{
	public:
		NoteTrack(std::vector<NoteTone> toneList);
		std::unordered_map<unsigned short int, NoteTone> tones;
		bool continous; // does it repeat "forever" ?
		unsigned int repeatCount; // if not continous, how many 2 measure intervals it will repeat for (0 means it will play only once and never repeat)
};

#endif 