// SourceNote
#include "Toolkit.h"
#include "Tempo.h"
#include "NoteTone.h"
#include "NoteTone.h"

// STK
#include "Instrmnt.h"
#include "JCRev.h"
#include "Sitar.h"
#include "Messager.h"
#include "RtAudio.h"

// std lib
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#define S_RATE 44100

using std::min;
using namespace stk;

// This is a main file for the algorithm team's tests.
// It should not be implemented in the final release.
int main(void) {
	
	Stk::setSampleRate( (float) S_RATE );
	
	//NoteTone a(1, 2, kSine, 440);
	
	Toolkit tk = Toolkit();
	tk.playTone(0, 2, "sine", 440.0);
	
	tk.startStream();
	
	Stk::sleep(10000);
	
	tk.stopStream();
	
	
	return 0;
}