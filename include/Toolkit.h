#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <string>

class Toolkit {	
	private:
		bool isSample;
	
	public:
		Toolkit();
		void playTone(std::string message);
};

#endif