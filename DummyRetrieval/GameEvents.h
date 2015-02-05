#pragma once
#ifndef __GAME_EVENTS_H__
#define __GAME_EVENTS_H__

#include <string>
#include <iostream>
#include <map>


// To add a new message type for random selection, add it to the enum below and give it a probability
// Then update MESSAGE_TYPE_SIZE.
typedef enum MESSAGE_TYPE_ {
	PLAYER_KILL,			// The player we are generating music for has killed an enemy player
	PLAYER_DEATH,			// The player we are generating music for has died
	FIRE_WEAPON,			// The player fired off a shot
	PLAYER_SWITCH_TEAMS,	// The player switched teams
	PLAYER_JUMP,				// The player jumped in-game
	PLAYER_HURT				// The player was fired at
} MESSAGE_TYPE;

#define PLAYER_KILL_PROB			0.018
#define PLAYER_DEATH_PROB			0.008
#define FIRE_WEAPON_PROB			0.3
#define PLAYER_SWITCH_TEAMS_PROB	0.002
#define PLAYER_JUMP_PROB			0.01
#define PLAYER_HURT_PROB			0.155

#define MESSAGE_TYPE_SIZE 6

// Probabilities used in dummy data provider
extern std::map<MESSAGE_TYPE, double> MessageTypeProbabilities;

// Reasons typically represent your attacker or victim.
// They can also represent things such as how much ammo is left in your clip.
// Note that here, they basically mean nothing, and that PLAYER_JUMP can occur because of "DEXTER_MORGAN".
// But in the real application, PLAYER_KILL's reason will be the person whom you killed, PLAYER_DEATH's
// reason will be the person that killed you, etc.
const std::string reasons[] = {
	"PLAYER_14",
	"PLAYER_11",
	"PLAYER_ONE",
	"GENEVIEVE",
	"ANAROK",
	"DEXTER_MORGAN",
	"ENCELADUS"
};

// GameMessage struct is used to pass messages between application components
typedef struct GameMessage_ {
	MESSAGE_TYPE messageType;
	std::string  info;
} GameMessage;


// Enable stream write operator to process the MESSAGE_TYPE enum
std::ostream& operator<<(std::ostream& out, const MESSAGE_TYPE val);

#endif