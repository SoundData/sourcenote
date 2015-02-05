#pragma once
#ifndef __DUMMY_DATA_PROVIDER_H__
#define __DUMMY_DATA_PROVIDER_H__


#include "GameEvents.h"
#include <thread>
#include <mutex>
#include <queue>
#include <random>

#define MSEC_GENERATE_DELAY 100			// ms to wait between trying to generate GameEvents
#define MSEC_PROCESS_DELAY 1000			// ms to wait between processing events waiting in the message queue

class DummyDataProvider
{
public:
	DummyDataProvider(std::mutex& mutex, std::queue<GameMessage>& q);
	~DummyDataProvider();
	void ProvideData();
	
private:
	std::mutex& mutex_; // Reference to mutex protecting MessageQueue
	std::queue<GameMessage>& msgQueue_; // Reference to MessageQueue
	std::mt19937 rng_;
	double GetRandomDoubleBetween(double, double);
	int GetRandomIntBetween(int, int);
};

#endif