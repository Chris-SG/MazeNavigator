#pragma once

#include <chrono>
#include <string>

/// <summary>
/// A ChronoTimer is a timer with millisecond precision.
/// Used to time certain parts of this program.
/// </summary>
class ChronoTimer
{
private:
	std::chrono::high_resolution_clock::time_point _startTime; //The time this clock started
	std::chrono::high_resolution_clock::time_point _endTime; //The time this clock ended
public:
	ChronoTimer();
	~ChronoTimer();

	void StartTimer();
	void EndTimer();

	std::string PrintTime_ms();
};