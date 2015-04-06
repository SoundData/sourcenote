#include "Toolkit.h"
#define MAX_VOICES 5

using std::min;
using namespace stk;

// ToneData is a helper struct that can be accessed from within the RtAudio tick function call
struct ToneData {
	Voicer voices;
	unsigned int samplesLeft[MAX_VOICES];
	bool isPlaying;
	
	ToneData()
		: isPlaying(false) {}
};

Toolkit::Toolkit() {
	std::cout << "Initialized the toolkit!" << std::endl;
	ToneData *data = new ToneData();
	now = 0;
	
	// Initialize the ToneData
	
	
	
	// Setup the RtAudio parameters
	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	
	// Initialize the DAC
	try {
		dac.openStream(&parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &Toolkit::mainTick, (void *)data);
	} catch(StkError &e) {
		std::cout << "Error starting the stream, sorry man.\n";
		return;
	}
}

Toolkit::~Toolkit() {
	// dac.closeStream();
}

// Turn up!
int Toolkit::startStream(void) {
	try {
		dac.startStream();
	} catch(StkError &e) {
		std::cout << "Error starting the stream, sorry man.\n";
		return 0;
	}
	
	return 1;
}

int Toolkit::mainTick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer) {
	ToneData *data = (ToneData *) dataPointer;
	StkFloat *samples = (StkFloat *) outputBuffer;
	int nTicks = (int) nBufferFrames;
	
	for(int i = 0; i < nTicks*2; i++) {
		//samples[nBufferFrames*0 + i]
		//samples[nBufferFrames*1 + i]
		//samples[i++] = data->gen->tick();
		//samples[i++] = samples[i-1];
	}
	
	//data->freq *= 1.005;
	//data->gen->setFrequency( data->freq );
	
	return 0;
}

int Toolkit::stopStream(void) {
	try {
		dac.closeStream();
	} catch ( RtAudioError &error ) {
		error.printMessage();
		return 1;
	}
	return 0;
}

void Toolkit::playNoteTone(NoteTone *t) {
	//std::cout << "Playing " << waveform << " tone @ freq " << freq << "Hz.\n";
	std::cout << "Playing waveform " << t->getWaveform() << " at frequency " << t->getFrequency() << "\n";
}

void Toolkit::playPercussionTone(PercussionTone *t) {
	std::cout << "Playing perc tone '" << t->getFileName() << "'.\n";
}