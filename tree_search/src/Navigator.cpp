#include <algorithm>
#include <iostream>

#include "../include/Navigator.h"
#include "../include/MapParser.h"
#include "../include/TextLogger.h"

using namespace std;


Navigator::Navigator(Grid2D* newGrid)
{
	newGrid->Clone(&_map);
}

/// <summary>
/// Constructor for a new Navigator
/// </summary>
/// <param name="width">The width of a new navigation course.</param>
/// <param name="height">The height of a new navigation course.</param>
Navigator::Navigator(int width, int height)
{
	//Create an array of arrays to represent height
	_map = new Grid2D(width, height);
}

/// <summary>
/// Destructor for Navigator
/// </summary>
Navigator::~Navigator()
{
	TextLogger::LOG("Deleting navigator", LOGGING_DEBUG);
	delete _map;
}

/// <summary>
/// Return the navigator's related map
/// </summary>
Grid2D* Navigator::GetMap()
{
	return _map;
}


/// <summary>
/// Start navigation!
/// </summary>
/// <param name="searchModule">Search algorithm module to use when navigating map</param>
void Navigator::Navigate(TreeSearch* searchModule)
{
	// We will store our path in this vector
	vector<SearchNode*> path;
	TextLogger::LOG("Solving path...", LOGGING_DEBUG);
	// Solve the maze using the given search module
	path = searchModule->Solve(_map);

	TextLogger::LOG("Path solved with length " + path.size(), LOGGING_DEFAULT);

	TextLogger::LOG("Updating map...", LOGGING_DEBUG);
	// Update map to reflect new positions (searched, not searched, path)
	searchModule->UpdateMap(_map);

	// Print out the solved map
	_map->PrintMap();

	TextLogger::LOG("Deleting nodes", LOGGING_DEBUG);
	searchModule->DeleteSearchedNodes();
	searchModule->DeleteSearchStack();
}


void Navigator::Clone(Navigator** newNavigator)
{
	*newNavigator = new Navigator(_map);
}