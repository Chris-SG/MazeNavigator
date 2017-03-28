#include "../include/MapParser.h"
#include "../include/Timer.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


MapParser::MapParser(string filename)
{
	_file = new fstream(filename, fstream::in);

	// consider adding checks
}

void MapParser::ReadFile(Navigator* to)
{
	ChronoTimer timer;
	timer.StartTimer();

	string lReadLine;
	int lLinesRead = 0;

	while (getline(*_file, lReadLine))
	{
		vector<string> lLineBroken;
		size_t pos;
		 
		if (strcmp(&lReadLine[0], "[") && strcmp(&lReadLine[lReadLine.size()-1], "]"))
		{
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), '['), lReadLine.end());
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), ']'), lReadLine.end());
			string br = ",";
			while ((pos = lReadLine.find(br)) != string::npos)
			{
				lLineBroken.push_back(lReadLine.substr(0, pos));
				lReadLine.erase(0, (pos + br.size()));
			}
			lLineBroken.push_back(lReadLine);

			// If not 2, error
			if (lLineBroken.size() == 2)
			{
				to = new Navigator(stoi(lLineBroken[0]), stoi(lLineBroken[1]));
			}
		}

		else if (strcmp(&lReadLine[0], "(") && strcmp(&lReadLine[lReadLine.size() - 1], ")"))
		{
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), '('), lReadLine.end());
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), ')'), lReadLine.end());
			string br = ",";

			while ((pos != lReadLine.find(br)) != string::npos)
			{
				lLineBroken.push_back(lReadLine.substr(0, pos));
				lReadLine.erase(0, (pos + br.size()));
			}
			lLineBroken.push_back(lReadLine);

			//lLinesRead should be 1 or 2 if 2, otherwise 4
			if (lLineBroken.size() == 2)
			{
				if (lLinesRead == 1)
				{
					to->GetMap()->AddStart(stoi(lLineBroken[0]), stoi(lLineBroken[1]));
				}
				else if (lLinesRead == 2)
				{
					to->GetMap()->AddEnd(stoi(lLineBroken[0]), stoi(lLineBroken[1]));
				}
			}
			else if (lLineBroken.size() == 4)
			{
				to->GetMap()->AddLocation(stoi(lLineBroken[0]), stoi(lLineBroken[1]), stoi(lLineBroken[2]), stoi(lLineBroken[3]));
			}
		}


		lLinesRead++;
	}

	timer.EndTimer();
	cout << "Map analyzed in " << timer.PrintTime_ms() << endl;
}