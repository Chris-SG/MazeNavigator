#include <iostream>
#include <sstream>

#include "../include/MapParser.h"
#include "../include/AStarSearch.h"
#include "../include/BreadthFirstSearch.h"
#include "../include/DepthFirstSearch.h"
#include "../include/GreedyBestFirstSearch.h"
#include "../include/Timer.h"
#include "../include/Image.h"
#include "../include/TextLogger.h"

using namespace std;

int main(int argc, char* argv[])
{
	int lCount = -1;
	int lDraw = 1;
	bool lLoggingChecked = false;
	stringstream lSs;
	// Initialize logging system
	if (argc >= 4)
	{
		for (int i = 3; i < argc-1; i++)
		{
			if (strcmp((argv[i]), "--d") == 0)
			{
				lDraw = stoi(argv[i + 1]);
			}
			if (strcmp((argv[i]), "--l") == 0)
			{
				TextLogger::OpenLog(stoi(argv[i + 1]));
				lLoggingChecked = true;
			}
			if (strcmp((argv[i]), "--c") == 0)
			{
				lCount = stoi(argv[i + 1]);
			}
		}
	}
	if(!lLoggingChecked)
	{
		TextLogger::OpenLog(LOGGING_DEFAULT);
	}

	// We need an input file
	if (argc < 2)
	{
		TextLogger::LOG("No input file provided.", LOGGING_DEFAULT);
		return 1;
	}
	// We also need a search algorithm
	else if (argc < 3)
	{
		TextLogger::LOG("No search method provided.", LOGGING_DEFAULT);
		cout << "Options are: AS, BFS, DFS, GBFS, ALL" << endl;
		return 2;
	}

	// Place to store our navigator
	Navigator* lNavigator = nullptr;

	// Exception handling
	try
	{
		int lMin, lMax, lAvg;
		// Read provided map file
		TextLogger::LOG("Opening map from file.", LOGGING_DEFAULT);
		MapParser lMap(argv[1]);
		lMap.ReadFile(lNavigator);

		// Print intial state of the map
		lNavigator->GetMap()->PrintMap();

		if (strcmp(argv[2], "AS") == 0)
		{
			// Searching using A* algorithm
			TextLogger::LOG("Solving using A* algorithm", LOGGING_DEFAULT);
			AStarSearch* lAS = new AStarSearch();
			int lMin = 0, lMax = 0, lAvg = 0;

			for (int i = 0; i < lCount; i++)
			{
				Navigator* lNavigatorToUse = nullptr;
				lNavigator->Clone(&lNavigatorToUse);
				TreeSearch* lSearchModule = nullptr;
				AStarSearch* lASTemp = new AStarSearch();

				lNavigatorToUse->Navigate(lASTemp);
				if (lAS->TimeTaken() < lMin || i == 0)
				{
					lMin = lASTemp->TimeTaken();
				}
				cout << "Compare " << lAS->TimeTaken() << " and " << lMax << endl;
				if (lAS->TimeTaken() > lMax)
				{
					cout << "update lmax " << endl;
					lMax = lASTemp->TimeTaken();
				}

				delete lNavigatorToUse;
				delete lASTemp;

				//lAvg = ((lAvg*(i + 1) + lAS->TimeTaken()) / (i+1));
			}
			lSs.str(string());
			lSs << "Min time: " << lMin << ", Max time: " << lMax << ", Avg time: " << lAvg;
			TextLogger::LOG(lSs.str(), LOGGING_DEFAULT);

			lNavigator->Navigate(lAS);
		}
		else if (strcmp(argv[2], "DFS") == 0)
		{
			// Searching using DFS algorithm
			TextLogger::LOG("Solving using Depth First Search algorithm", LOGGING_DEFAULT);
			DepthFirstSearch* lDFS = new DepthFirstSearch();
			lNavigator->Navigate(lDFS);
		}
		else if (strcmp(argv[2], "BFS") == 0)
		{
			// Searching using BFS algorithm
			TextLogger::LOG("Solving using Breadth First Search algorithm", LOGGING_DEFAULT);
			BreadthFirstSearch* lBFS = new BreadthFirstSearch();
			lNavigator->Navigate(lBFS);
		}
		else if (strcmp(argv[2], "GBFS") == 0)
		{
			// Searching using GBFS algorithm
			TextLogger::LOG("Solving using Greedy Best First Search algorithm", LOGGING_DEFAULT);
			GreedyBestFirstSearch* lGBFS = new GreedyBestFirstSearch();
			lNavigator->Navigate(lGBFS);
		}
		else if (strcmp(argv[2], "NONE") == 0)
		{
			TextLogger::LOG("Printing map, no search algorithm used.", LOGGING_DEFAULT);
			lNavigator->GetMap()->PrintMap();
		}
		else if (strcmp(argv[2], "ALL") == 0)
		{

			TextLogger::LOG("Solving using all algorithms.", LOGGING_DEFAULT);
			for (int i = 0; i < 4; i++)
			{
				Navigator* lNavigatorToUse = nullptr;
				lNavigator->Clone(&lNavigatorToUse);
				TreeSearch* lSearchModule = nullptr;

				if (i == 0)
				{

					TextLogger::LOG("Solving with A*.", LOGGING_DEBUG);
					lSearchModule = new AStarSearch();
				}
				else if (i == 1)
				{
					TextLogger::LOG("Solving with DFS.", LOGGING_DEBUG);
					lSearchModule = new DepthFirstSearch();
				}
				else if (i == 2)
				{
					TextLogger::LOG("Solving with BFS.", LOGGING_DEBUG);
					lSearchModule = new BreadthFirstSearch();
				}
				else if (i == 3)
				{
					TextLogger::LOG("Solving with GBFS.", LOGGING_DEBUG);
					lSearchModule = new GreedyBestFirstSearch();
				}

				lNavigatorToUse->Navigate(lSearchModule);

				delete lSearchModule;
				delete lNavigatorToUse;
			}
		}
		else
		{
			TextLogger::LOG("Invalid navigation mode provided.", LOGGING_FATAL);

			return 2;
		}

	}
	catch (exception& e)
	{
		lSs.str(string());
		lSs << "Exception occurred: " << e.what();
		TextLogger::LOG(lSs.str(), LOGGING_FATAL);

		return 2;
	}

	if (lDraw)
	{
		vector<colour>* lColours = new vector<colour>();
		colour lColour;

		TextLogger::LOG("Adding colours to vector.", LOGGING_DEBUG);
		lColour = { 255, 255, 255 }; // empty space colour
		lColours->push_back(lColour);
		lColour = { 0, 0, 0 }; // blocked colour
		lColours->push_back(lColour);
		lColour = { 0, 255, 0 }; // start position colour
		lColours->push_back(lColour);
		lColour = { 255, 0, 0 }; // end colour
		lColours->push_back(lColour);
		lColour = { 255, 255, 0 }; // path colour
		lColours->push_back(lColour);
		lColour = { 0, 255, 255 }; // searched nodes colour
		lColours->push_back(lColour);
		lColour = { 255, 0, 255 }; // unsearched nodes colour
		lColours->push_back(lColour);

		string lFileName = argv[1];
		lFileName += "_";
		lFileName += argv[2];
		lFileName += ".bmp";

		lSs.str(string());
		lSs << "Writing image to " << lFileName;
		TextLogger::LOG(lSs.str(), LOGGING_DEFAULT);
		ImageWriter::WriteImage(lFileName, lNavigator->GetMap()->GetGrid(), lColours, lNavigator->GetMap()->GridSize().x, lNavigator->GetMap()->GridSize().y, IMAGESIZEPERNODE);
	}


	delete lNavigator;

	TextLogger::CloseLog();
	return 0;
}