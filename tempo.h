class Tempo{
	public:
		void start();

	private:
		unsigned int bpm;
		bool isRunning;
		static void* run(void*);
};