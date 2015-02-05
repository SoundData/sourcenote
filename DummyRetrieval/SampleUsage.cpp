#include "DummyDataProvider.h"
#include "GameEvents.h"

#define MAP_PROB(p) MessageTypeProbabilities[p] = p ## _PROB

void ProcessItem(const GameMessage&);

int main()
{
	// Fill in probabilities used by the data generator
	// These items are configured inside GameEvents.h
	MAP_PROB(PLAYER_KILL);
	MAP_PROB(PLAYER_DEATH);
	MAP_PROB(FIRE_WEAPON);
	MAP_PROB(PLAYER_SWITCH_TEAMS);
	MAP_PROB(PLAYER_JUMP);
	MAP_PROB(PLAYER_HURT);
	// Insert extra MAP_PROB calls to assign probabilities as needed

	// Protects access to the GameMessage queue that will be added to asynchronously
	std::mutex mtx;
	// Holds important GameMessages from the game server
	std::queue<GameMessage> q;

	// Start the thread that will provide data to the GameMessage queue
	DummyDataProvider ddp(mtx, q);
	std::thread t(&DummyDataProvider::ProvideData, std::ref(ddp));

	// Main processing loop
	// Wait for queue to be populated and perform some work on it when items are available
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(MSEC_PROCESS_DELAY));
		mtx.lock();
		//std::cout << "Main thread got lock, processing all available items" << std::endl;
		while (!q.empty())
		{
			// Process this item 
			ProcessItem(q.front());
			q.pop();
		}
		mtx.unlock();
	}
}

void ProcessItem(const GameMessage& gm)
{
	std::cout << "\tProcessing item [" << gm.messageType << "]: " << gm.info << std::endl;
	// Speed up BPM, queue a bass kick on the next downbeat, decrease synth freq..
}