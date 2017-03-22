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
	_width = width;
	_height = height;

	//Create an array of arrays to represent height
	_map = new int*[height];
	//Iterate over all rows
	for (int i = 0; i < height; i++)
	{
		//Create an array to represent width
		_map[i] = new int[width];

		//Iterate over all columns
		for (int j = 0; j < width; j++)
		{
			//Set map space to empty
			_map[i][j] = CLEAR;
		}
	}
}

/// <summary>
/// Destructor for Navigator
/// </summary>
Navigator::~Navigator()
{
	for (int i = 0; i < _width; i++)
	{
		delete[] _map[i];
	}

	delete[] _map;
}

/// <summary>
/// Add a new blocked location
/// <summary>
/// <param name="x">The first point along the x axis</param>
/// <param name="y">The first point along the y axis</param>
/// <param name="w">The width the blockage spans across the x axis</param>
/// <param name="h">The width the blockage spans across the y axis</param>
void Navigator::AddLocation(int x, int y, int w, int h)
{
	//Ensure the blockage is being placed within the map
	if (x > _width || y > _height)
	{
		return;
	}

	//Iterate over relevant rows. Ensure starts counting from 0 or higher
	for (int i = max(0, y); i < min(h, (_height-y)); i++)
	{
		//Iterate over relevant columns. Ensure starts counting from 0 or higher
		for (int j = max(0, x); i < min(w, (_width-x)); i++)
		{
			//Block that section
			_map[i][j] = BLOCKED;
		}
	}
}

/// <summary>
/// Add start and create start node
/// </summary>
/// <param name="x">X position of start</param>
/// <param name="y">Y position of start</param>
void Navigator::AddStart(int x, int y)
{
	_posX = x;
	_posY = y;

	Point2D start;
	start.x = _posX;
	start.y = _posY;

	_startNode = new SearchNode(start);
	_map[_posX][_posY] = POSITION;
}

/// <summary>
/// Add end and create end node
/// </summary>
/// <param name="x">X position of end</param>
/// <Param name="y">Y position of end</param>
void Navigator::AddEnd(int x, int y)
{
	_endX = x;
	_endY = y;

	Point2D endPt;
	endPt.x = _endX;
	endPt.y = _endY;

	_endNode = new SearchNode(endPt);
	_map[_endX][_endY] = END;
}

/// <summary>
/// Start navigation!
/// </summary>
/// <param name="searchModule">Search algorithm module to use when navigating map</param>
void Navigator::Navigate(TreeSearch& searchModule)
{
	vector<SearchNode*> path;

	path = searchModule.Solve(_startNode, _endNode);

	// perhaps move map to a separate object?
}