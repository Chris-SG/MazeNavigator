#pragma once

#include <chrono>
#include <string>

class ChronoTimer
{
private:
	std::chrono::high_resolution_clock::time_point _startTime;
	std::chrono::high_resolution_clock::time_point _endTime;
public:
	ChronoTimer();
	~ChronoTimer();

	void StartTimer();
	void EndTimer();

	std::string PrintTime_ms();
};