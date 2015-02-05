#include "DummyDataProvider.h"
#include <ctime>
#include <chrono>

// DummyDataProvider ctor takes references to the MessageQueue and the mutex protecting it
DummyDataProvider::DummyDataProvider(std::mutex& mutex, std::queue<GameMessage>& q)
	:mutex_(mutex),
	msgQueue_(q)
{
	rng_.seed((unsigned long)std::time(0));
}

void DummyDataProvider::ProvideData()
{
	while (true)
	{
		bool lock = mutex_.try_lock();
		if (lock)
		{
			GameMessage gm;
			int mt = -1;
			double d = GetRandomDoubleBetween(0, 1);

			// Choose a message type (or perhaps none)
			for (auto &x : MessageTypeProbabilities)
			{
				d -= x.second;
				if (d < 0)
				{
					mt = (int)x.first;
					break;
				}
			}

			// Don't add anything to the queue this time around
			if (mt == -1)
			{
				mutex_.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(MSEC_GENERATE_DELAY));
				continue;
			}

			// Push this message type and some random extra informatino onto the queue
			gm.messageType = (MESSAGE_TYPE)mt;
			std::cout << "Generated data for event [" << gm.messageType << "]" << std::endl;
			gm.info = reasons[GetRandomIntBetween(0, 6)];
			msgQueue_.push(gm);
			mutex_.unlock();

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(MSEC_GENERATE_DELAY));
	}
}

DummyDataProvider::~DummyDataProvider()
{
	// I don't care, do what you want
	// 
	std::cout << "Dummy data provider destroyed." << std::endl;
}

inline double DummyDataProvider::GetRandomDoubleBetween(double low, double hi)
{
	return std::uniform_real_distribution<double>(low, hi)(rng_);
}

inline int DummyDataProvider::GetRandomIntBetween(int low, int hi)
{
	return std::uniform_int_distribution<int>(low, hi)(rng_);
}