#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

#include "../include/TextLogger.h"

using namespace std;

namespace TextLogger
{
	int gLoggingLevel = 0;
	fstream gLogFile;

	/// <summary>
	/// Allows the program to log a text line to file
	/// </summary>
	/// <param name="logText">Text to log to file</param>
	/// <param name="logLevel">Logging level required to log the text</param>
	void LOG(string logText, int logLevel)
	{
		// Ensure our file is open and we actually want to log
		if (logLevel <= gLoggingLevel && gLogFile.good())
		{
			gLogFile << logText << endl;
			cout << logText << endl;
		}
	}

	/// <summary>
	/// Opens a new log file with a given log level
	/// </summary>
	/// <param name="logLeve">Level of logging severity</param>
	/// <param name="logName">A name to save the log as</param>
	void OpenLog(int logLevel, string logName)
	{
		// Set our logging level
		gLoggingLevel = logLevel;

		// Ensure logging isn't disabled
		if (logLevel != LOGGING_OFF)
		{
			// If the name provided is simply "none"
			if (logName == "none")
			{
				// We will setup a log name using the current date and time, YYYY-mm-dd HH-MM-SS.log
				time_t lTime = std::time(nullptr);
				struct tm lTimeInfo;
				localtime_s(&lTimeInfo, &lTime);

				stringstream lSs;
				lSs << put_time(&lTimeInfo, "%Y-%m-%d %H-%M-%S.log");
				logName = lSs.str();
			}
			// Open the file using the given name
			gLogFile.open(logName, fstream::out);

			switch (logLevel)
			{
			case LOGGING_FATAL:
				gLogFile << logName << endl << "LOGGING MODE: FATAL" << endl << endl;
				break;
			case LOGGING_DEFAULT:
				gLogFile << logName << endl << "LOGGING MODE: DEFAULT" << endl << endl;
				break;
			case LOGGING_DEBUG:
				gLogFile << logName << endl << "LOGGING MODE: DEBUG" << endl << endl;
				break;
			}
		}
	}

	/// <summary>
	/// Close an open log
	/// </summary>
	void CloseLog()
	{
		// Check that we actually have a file we are logging to
		if(gLogFile.good())
			gLogFile.close();
	}
}