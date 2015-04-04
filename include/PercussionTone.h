#ifndef __PERCUSSIONTONE_H_INCLUDED__
#define __PERCUSSIONTONE_H_INCLUDED__

#include "Tone.h"
#include <string>

class PercussionTone: public Tone{
	private:
		std::string fileName;

	public:
		PercussionTone(unsigned int startTime, std::string fileName);
		PercussionTone(){}; //Required to access a NoteTone in a vector of NoteTones. My research suggests its a Clang specific issue.
		std::string getFileName();
};

#endif 