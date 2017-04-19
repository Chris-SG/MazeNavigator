#include "../include/Timer.h"

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

time_t ChronoTimer::GetTime_ms()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count();
}