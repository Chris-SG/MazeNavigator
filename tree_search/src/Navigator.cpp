#include <algorithm>

#include "../include/Navigator.h"
#include "../include/MapParser.h"

using namespace std;

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
	delete _map;
}



/// <summary>
/// Start navigation!
/// </summary>
/// <param name="searchModule">Search algorithm module to use when navigating map</param>
void Navigator::Navigate(TreeSearch* searchModule)
{
	vector<SearchNode*> path;

	path = searchModule->Solve(_map);
}