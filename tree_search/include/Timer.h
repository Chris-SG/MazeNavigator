#pragma once

#include <chrono>
#include <iostream>

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

ChronoTimer::ChronoTimer()
{

}

ChronoTimer::~ChronoTimer()
{

}

void ChronoTimer::StartTimer()
{
	_startTime = std::chrono::high_resolution_clock::now();
}

void ChronoTimer::EndTimer()
{
	_endTime = std::chrono::high_resolution_clock::now();
}

std::string ChronoTimer::PrintTime_ms()
{
	return (std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count()) + "ms");
}