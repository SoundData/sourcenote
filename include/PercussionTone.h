#ifndef __PERCUSSIONTONE_H_INCLUDED__
#define __PERCUSSIONTONE_H_INCLUDED__

#include "Tone.h"
#include <string>

class PercussionTone: public Tone{
	private:
		std::string fileName;

	public:
		PercussionTone(unsigned int startTime, std::string fileName);
		std::string getFileName();
};

#endif 