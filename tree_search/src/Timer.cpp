#include "../include/Timer.h"

/// <summary>
/// Constructor for our timer
/// </summary>
ChronoTimer::ChronoTimer()
{

}

/// <summary>
/// Destructor for our timer
/// </summary>
ChronoTimer::~ChronoTimer()
{

}

/// <summary>
/// Start our timer
/// </summary>
void ChronoTimer::StartTimer()
{
	// Use current time
	_startTime = std::chrono::high_resolution_clock::now();
}

/// <summary>
/// End our timer
/// </summary>
void ChronoTimer::EndTimer()
{
	// Use current time
	_endTime = std::chrono::high_resolution_clock::now();
}

/// <summary>
/// Return the time as a string
/// </summary>
std::string ChronoTimer::PrintTime_ms()
{
	// Get time diff between end and start
	return (std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count()) + "ms");
}

/// <summary>
/// Returns the time as a time_t
/// </summary>
time_t ChronoTimer::GetTime_ms()
{
	// Get time diff between end and start
	return std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count();
}