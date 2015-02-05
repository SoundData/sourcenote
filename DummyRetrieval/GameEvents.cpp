#include "GameEvents.h"

// Implement the MessageTypesProbabilities declared in the GameEvents.h header as a global
std::map<MESSAGE_TYPE, double> MessageTypeProbabilities;

// Provide a nice way to print the MESSAGE_TYPE enum to an output stream
std::ostream&
operator<<(std::ostream& out, const MESSAGE_TYPE val)
{
	const char *result = 0;
#define PROCESS_VAL(p) case(p): result = #p; break;
	switch (val) {
		PROCESS_VAL(PLAYER_KILL);
		PROCESS_VAL(PLAYER_DEATH);
		PROCESS_VAL(FIRE_WEAPON);
		PROCESS_VAL(PLAYER_SWITCH_TEAMS);
		PROCESS_VAL(PLAYER_JUMP);
		PROCESS_VAL(PLAYER_HURT);
	}
#undef PROCESS_VAL

	return out << result;
}