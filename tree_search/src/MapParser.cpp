#include <vector>
#include <algorithm>
#include <iostream>

#include "../include/MapParser.h"
#include "../include/Timer.h"
#include "../include/TextLogger.h"
#include "../include/TreeSearchExceptions.h"

using namespace std;



/// <summary>
/// Constructor for the MapParser
/// </summary>
/// <param name="filename">File we want to parse</param>
MapParser::MapParser(string filename)
{
	_file = new fstream(filename, fstream::in); //Open file
	if (!_file->good())
	{
		throw invalidfile;
	}
}

/// <summary>
/// Parse file provided and add map information to navigator provided
/// </summary>
/// <param name="to">Navigator to attach map to</param>
void MapParser::ReadFile(Navigator*& to)
{
	TextLogger::LOG("Parsing provided file", LOGGING_DEBUG);
	// Time how long parsing the map will take
	ChronoTimer timer;
	timer.StartTimer();

	string lReadLine; // Stores currently read line
	int lLinesRead = 0; // Store how many lines we have read

	// Continue while we can still get a new line from the file
	// Using while(true) to ensure all lines get parsed
	while (true)
	{
		if (!getline(*_file, lReadLine))
		{
			TextLogger::LOG("All lines read", LOGGING_DEBUG);
			break;
		}
		vector<string> lLineBroken;
		size_t pos;
		 
		// If our line is contained within [] brackets
		if (lReadLine[0]=='[' && lReadLine[lReadLine.size()-1]==']')
		{
			TextLogger::LOG("Found map size line: " + lReadLine, LOGGING_DEBUG);
			// Erase the brackets, we don't need them anymore.
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), '['), lReadLine.end());
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), ']'), lReadLine.end());
			string br = ","; // We will break the string at all commas

			// While we find a new comma
			while ((pos = lReadLine.find(br)) != string::npos)
			{
				// Add the text to our vector
				lLineBroken.push_back(lReadLine.substr(0, pos));
				// Erase text from string
				lReadLine.erase(0, (pos + br.size()));
			}
			// Push back the final part
			lLineBroken.push_back(lReadLine);

			// If not 2 parts
			if (lLineBroken.size() == 2)
			{
				// Create a navigator using the found parameters as the map size
				to = new Navigator(stoi(lLineBroken[1]), stoi(lLineBroken[0]));
			}
		}
		// If our line is contained within () brackets
		else if (lReadLine[0]=='(' && lReadLine[lReadLine.size() - 1]==')')
		{
			//Erase the brackets, we don't need them anymore
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), '('), lReadLine.end());
			lReadLine.erase(remove(lReadLine.begin(), lReadLine.end(), ')'), lReadLine.end());
			string br = ","; // Use comma as break text

			// While we can find a breakpoint
			while ((pos = lReadLine.find(br)) != string::npos)
			{
				// Add to vector and erase from string
				lLineBroken.push_back(lReadLine.substr(0, pos));
				lReadLine.erase(0, (pos + br.size()));
			}
			lLineBroken.push_back(lReadLine);

			//lLinesRead should be 1 or 2 if 2, otherwise 4
			if (lLineBroken.size() == 2)
			{
				// If it is the second line to be read, we use these co-ordinates for the start
				if (lLinesRead == 1)
				{
					TextLogger::LOG("Found map start: " + lReadLine, LOGGING_DEBUG);
					to->GetMap()->AddStart(stoi(lLineBroken[0]), stoi(lLineBroken[1]));
				}
				// If it is the third line to be read, we use these co-ordinates for the end
				else if (lLinesRead == 2)
				{
					TextLogger::LOG("Found map end: " + lReadLine, LOGGING_DEBUG);
					to->GetMap()->AddEnd(stoi(lLineBroken[0]), stoi(lLineBroken[1]));
				}
			}
			
			// ALl other lines are blocked locations, so block all them off
			else if (lLineBroken.size() == 4)
			{
				TextLogger::LOG("Found map wall: " + lReadLine, LOGGING_DEBUG);
				to->GetMap()->AddLocation(stoi(lLineBroken[0]), stoi(lLineBroken[1]), stoi(lLineBroken[2]), stoi(lLineBroken[3]));
			}
		}

		// Increment line count
		lLinesRead++;
	}

	timer.EndTimer(); // End timer
	TextLogger::LOG("Map analyzed in " + timer.PrintTime_ms(), LOGGING_DEFAULT);
}