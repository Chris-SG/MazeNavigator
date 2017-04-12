#include <iostream>

#include "../include/MapParser.h"
#include "../include/AStarSearch.h"
#include "../include/BreadthFirstSearch.h"
#include "../include/DepthFirstSearch.h"
#include "../include/GreedyBestFirstSearch.h"
#include "../include/Timer.h"
#include "../include/Image.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Must include file to parse!" << endl;
		return 1;
	}
	else if (argc < 3)
	{
		cout << "Must include a search method!" << endl;
		cout << "Options are: A*, BFS, DFS, GBFS" << endl;
		return 2;
	}

	Navigator* lNavigator = nullptr;

	try
	{
		MapParser lMap(argv[1]);
		lMap.ReadFile(lNavigator);

		lNavigator->GetMap()->PrintMap();

		if (strcmp(argv[2], "A*") == 0)
		{
			AStarSearch* lAS = new AStarSearch();
			lNavigator->Navigate(lAS);
		}
		else if (strcmp(argv[2], "DFS") == 0)
		{
			DepthFirstSearch* lDFS = new DepthFirstSearch();
			lNavigator->Navigate(lDFS);
		}
		else if (strcmp(argv[2], "BFS") == 0)
		{
			BreadthFirstSearch* lBFS = new BreadthFirstSearch();
			lNavigator->Navigate(lBFS);
		}
		else if (strcmp(argv[2], "GBFS") == 0)
		{
			GreedyBestFirstSearch* lGBFS = new GreedyBestFirstSearch();
			lNavigator->Navigate(lGBFS);
		}
		else
		{
			cout << "Invalid navigation mode \"" << argv[2] << "\"." << endl;
		}

	}
	catch (exception& e)
	{
		cout << "An exception occurred: " << e.what() << endl;

		return 2;
	}

	vector<colour>* lColours = new vector<colour>();
	colour lColour;

	lColour = { 255, 255, 255 }; // empty space colour
	lColours->push_back(lColour);
	lColour = { 0, 0, 0 }; // blocked colour
	lColours->push_back(lColour);
	lColour = { 128, 128, 128 }; // start position colour
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

	ImageWriter::WriteImage(lFileName, lNavigator->GetMap()->GetGrid(), lColours, lNavigator->GetMap()->GridSize().x, lNavigator->GetMap()->GridSize().y);

	cout << "Cleaning up..." << endl;
	
	delete lNavigator;

	return 0;
}