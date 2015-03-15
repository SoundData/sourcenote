#include "PercussionTone.h"
#include <string>

PercussionTone::PercussionTone(unsigned int startTime, std::string fileName) : Tone(startTime), fileName(fileName) {};

std::string PercussionTone::getFileName(){
	return fileName;
}