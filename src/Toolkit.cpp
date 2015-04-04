// main stuff
#include "Toolkit.h"

#define MAX_CHANNELS 0

using std::min;
using namespace stk;

struct ToneData {
	SineWave *s;
};

Toolkit::Toolkit() {
	std::cout << "Initialized the toolkit!" << std::endl;
	ToneData *data = new ToneData();
	now = 0;
	
	// Initialize the ToneData
	data->s = new SineWave();
	data->s->setFrequency( (StkFloat) 440.0 );
	
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
	
	for(int i = 0; i < nTicks; i++) {
		*samples++ = data->s->tick();
	}
	
	data->s->getFrequency()
	
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

void Toolkit::playTone(unsigned int start, int duration, std::string waveform, float freq) {
	std::cout << "Playing " << waveform << " tone @ freq " << freq << "Hz.\n";
}