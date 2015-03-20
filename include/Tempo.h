#ifndef __TEMPO_H_INCLUDED__
#define __TEMPO_H_INCLUDED__

class Tempo{
	private:
		unsigned int bpm;
		bool isRunning;
		static void* run(void*);

	public:
		Tempo(int beatsPerMinute);
		void start();
		void stop();
};

#endif