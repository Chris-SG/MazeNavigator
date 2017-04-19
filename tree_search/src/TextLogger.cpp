#include "../include/TextLogger.h"

#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

namespace TextLogger
{
	int gLoggingLevel = 0;
	fstream gLogFile;

	void LOG(string logText, int logLevel)
	{
		if (logLevel <= gLoggingLevel && gLogFile.good())
		{
			gLogFile << logText << endl;
			cout << logText << endl;
		}
	}

	void OpenLog(int logLevel, string logName)
	{
		gLoggingLevel = logLevel;
		if (logLevel != LOGGING_OFF)
		{
			if (logName == "none")
			{
				time_t lTime = std::time(nullptr);
				struct tm lTimeInfo;
				localtime_s(&lTimeInfo, &lTime);

				stringstream lSs;
				lSs << put_time(&lTimeInfo, "%Y-%m-%d %H-%M-%S.log");
				logName = lSs.str();
			}
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

	void CloseLog()
	{
		if(gLogFile.good())
			gLogFile.close();
	}
}