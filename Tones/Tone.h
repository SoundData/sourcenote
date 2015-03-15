#ifndef __TONE_H_INCLUDED__
#define __TONE_H_INCLUDED__

class Tone{
	private:
		unsigned int startTime;

	public:
		Tone(int startTime);
		unsigned int getStartTime();
};

#endif 