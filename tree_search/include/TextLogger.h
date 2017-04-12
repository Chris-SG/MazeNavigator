#pragma once
#include <string>
#include <fstream>

#define LOGGING_FATAL 0
#define LOGGING_DEFAULT 1
#define LOGGING_DEBUG 2

namespace TextLogger
{
	extern int gLoggingLevel;
	extern std::fstream gLogFile;

	void OpenLog(int logLevel = 1, std::string logName = "none");
	void CloseLog();
	void LOG(std::string logText, int logLevel);
}