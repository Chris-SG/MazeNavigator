#include <sstream>
#include <iostream>

// Navigation files
#include "../include/MapParser.h"
#include "../include/AStarSearch.h"
#include "../include/BreadthFirstSearch.h"
#include "../include/DepthFirstSearch.h"
#include "../include/GreedyBestFirstSearch.h"

// Additional includes
#include "../include/Timer.h"
#include "../include/Image.h"
#include "../include/TextLogger.h"

using namespace std;

void MultiSearch(Navigator* nav, int count, string search);

int main(int argc, char* argv[])
{
	int lCount = -1; // Count stores how many tests to do in the case of a multisearch
	int lDraw = 1; // Draw determines whether or not we will draw a picture after searching
	bool lLoggingChecked = false; // We don't want to accidently create two logs
	stringstream lSs;

	// Checks if help is requested
	if (argc >= 2 && strcmp(argv[1], "--help") == 0)
	{
		cout << "NAVIGATOR HELP" << endl;
		cout << "LAUNCH FORMAT: tree_search.exe {mapfile} {searchtype} [param arg] ..." << endl;
		cout << "\tmapfile must use a correct format. Examples can be found in the maps folder." << endl;
		cout << "\tsearchtype must be a valid search algorithm. Options are: AS, DFS, BFS, GBFS, ALL" << endl;
		cout << "\tAdditional parameters are optional. The argument for a parameter must follow the parameter, eg: --l 1" << endl;
		cout << "\tAll params must be prefixed with two dashes (--). List of params as follows:" << endl;
		cout << "\t--d" << endl;
		cout << "\t\tWhether or not an image should be drawn. Argument can be 0 (off) or 1 (on)" << endl;
		cout << "\t--l" << endl;
		cout << "\t\tLogging mode to use. Arguments are -1 (no logging), 0 (FATAL only), 1 (DEFAULT), 2 (DEBUG)" << endl;
		cout << "\t--c" << endl;
		cout << "\t\tCount for multisearch. Allows for an average of a given search mode on a map. Value can be any number greater than 0" << endl;
	}

	// We only check for additional launch params if we have more than 3 arguments
	if (argc >= 4)
	{
		// Check to argc-1 so we don't end up out-of-range
		for (int i = 3; i < argc-1; i++)
		{
			// --d refers to drawing a picture
			if (strcmp((argv[i]), "--d") == 0)
			{
				lDraw = stoi(argv[i + 1]);
			}

			// --l refers to what kind of log we want
			if (strcmp((argv[i]), "--l") == 0)
			{
				TextLogger::OpenLog(stoi(argv[i + 1]));
				lLoggingChecked = true;
			}

			// --c refers to multisearch test
			if (strcmp((argv[i]), "--c") == 0)
			{
				lCount = stoi(argv[i + 1]);
			}
		}
	}

	// If we made a log using a launch param, we can skip this
	if(!lLoggingChecked)
	{
		TextLogger::OpenLog(LOGGING_DEFAULT);
	}

	// Logging is setup before anything else to ensure errors can be added to it

	// We need an input file
	if (argc < 2)
	{
		TextLogger::LOG("No input file provided.", LOGGING_FATAL);
		TextLogger::LOG("Please use --help for assistance running this program.", LOGGING_FATAL);
		return 1;
	}
	// We also need a search algorithm
	else if (argc < 3)
	{
		TextLogger::LOG("No search method provided.", LOGGING_FATAL);
		TextLogger::LOG("Options are: AS, BFS, DFS, GBFS, ALL", LOGGING_FATAL);
		TextLogger::LOG("Please use --help for assistance running this program.", LOGGING_FATAL);
		return 2;
	}

	// Place to store our navigator
	Navigator* lNavigator = nullptr;

	// Exception handling
	try
	{
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

			if (lCount > 0)
				MultiSearch(lNavigator, lCount, "AS");

			lNavigator->Navigate(lAS);
		}
		else if (strcmp(argv[2], "DFS") == 0)
		{
			// Searching using DFS algorithm
			TextLogger::LOG("Solving using Depth First Search algorithm", LOGGING_DEFAULT);
			DepthFirstSearch* lDFS = new DepthFirstSearch();

			if (lCount > 0)
				MultiSearch(lNavigator, lCount, "DFS");

			lNavigator->Navigate(lDFS);
		}
		else if (strcmp(argv[2], "BFS") == 0)
		{
			// Searching using BFS algorithm
			TextLogger::LOG("Solving using Breadth First Search algorithm", LOGGING_DEFAULT);
			BreadthFirstSearch* lBFS = new BreadthFirstSearch();

			if (lCount > 0)
				MultiSearch(lNavigator, lCount, "BFS");

			lNavigator->Navigate(lBFS);
		}
		else if (strcmp(argv[2], "GBFS") == 0)
		{
			// Searching using GBFS algorithm
			TextLogger::LOG("Solving using Greedy Best First Search algorithm", LOGGING_DEFAULT);
			GreedyBestFirstSearch* lGBFS = new GreedyBestFirstSearch();

			if (lCount > 0)
				MultiSearch(lNavigator, lCount, "GBFS");

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
				// We need clones of our navigator as they are single use objects
				Navigator* lNavigatorToUse = nullptr;
				lNavigator->Clone(&lNavigatorToUse);
				TreeSearch* lSearchModule = nullptr;

				if (i == 0)
				{

					TextLogger::LOG("Solving with A*.", LOGGING_DEBUG);
					lSearchModule = new AStarSearch();
					if (lCount > 0)
						MultiSearch(lNavigator, lCount, "AS");
				}
				else if (i == 1)
				{
					TextLogger::LOG("Solving with DFS.", LOGGING_DEBUG);
					lSearchModule = new DepthFirstSearch();
					if (lCount > 0)
						MultiSearch(lNavigator, lCount, "DFS");
				}
				else if (i == 2)
				{
					TextLogger::LOG("Solving with BFS.", LOGGING_DEBUG);
					lSearchModule = new BreadthFirstSearch();
					if (lCount > 0)
						MultiSearch(lNavigator, lCount, "BFS");
				}
				else if (i == 3)
				{
					TextLogger::LOG("Solving with GBFS.", LOGGING_DEBUG);
					lSearchModule = new GreedyBestFirstSearch();
					if (lCount > 0)
						MultiSearch(lNavigator, lCount, "GBFS");
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
		TextLogger::LOG("Please use --help for assistance running this program.", LOGGING_FATAL);

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

/// <summary>
/// Search using the same algorithm multiple times
/// Allows for an average search time
/// </summary>
/// <param name="nav">The navigator to use. We will clone this.</param>
/// <param name="count">How many searches we want to do</param>
/// <param name="search">Search algorithm to use</param>
void MultiSearch(Navigator* nav, int count, string search)
{
	// Values for search time
	int lMin = 0, lMax = 0;
	float lAvg = 0.0;

	// Let's do this for how many times requested
	for (int i = 0; i < count; i++)
	{
		// We clone the navigator since it is a single use object
		Navigator* lNavigatorToUse = nullptr;
		nav->Clone(&lNavigatorToUse);
		TreeSearch* lSearchModule = nullptr;
		TreeSearch* lSearch;

		// Detect what search algorithm to use. Again, a search algorithm is single use
		if (search == "AS")
			lSearch = new AStarSearch();
		else if (search == "BFS")
			lSearch = new BreadthFirstSearch();
		else if (search == "DFS")
			lSearch = new DepthFirstSearch();
		else if (search == "GBFS")
			lSearch = new GreedyBestFirstSearch();
		else break;

		// Navigate the maze
		lNavigatorToUse->Navigate(lSearch);

		// Do we have a new minimum time?
		if (lSearch->TimeTaken() < lMin || i == 0)
		{
			lMin = lSearch->TimeTaken();
		}
		// Do we have a new maximum time?
		if (lSearch->TimeTaken() > lMax)
		{
			lMax = lSearch->TimeTaken();
		}
		// We want an average time over all searches
		lAvg = (((lAvg*i) + lSearch->TimeTaken()) / (i + 1));

		// Clean up the unneeded objects
		delete lNavigatorToUse;
		delete lSearch;

	}
	stringstream lSs;
	lSs.str(string());
	lSs << "Search module: " << search << ", Min time: " << lMin << ", Max time: " << lMax << ", Avg time: " << lAvg << " (" << count << " tests)";
	TextLogger::LOG(lSs.str(), LOGGING_OFF);
}