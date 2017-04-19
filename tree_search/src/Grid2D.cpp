#include <algorithm>
#include <iostream>
#include <sstream>

#include "../include/Grid2D.h"
#include "../include/TextLogger.h"

using namespace std;

/// <summary>
/// Constructor for grid using a given width and height
/// </summary>
/// <param name="width">Width of the grid</param>
/// <param name="height">Height of the grid</param>
Grid2D::Grid2D(int width, int height)
{
	stringstream lSs;

	_width = width;
	_height = height;

	//Create an array of arrays to represent height
	_map = new char*[height];
	//Iterate over all rows
	for (int i = 0; i < height; i++)
	{
		//Create an array to represent width
		_map[i] = new char[width];

		//Iterate over all columns
		for (int j = 0; j < width; j++)
		{
			//Set map space to empty
			lSs.str(string());
			lSs << "Clearing map space at (" << j << "," << i << ")";
			TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
			_map[i][j] = CLEAR;
		}
	}
}

/// <summary>
/// Destructor for grid
/// </summary>
Grid2D::~Grid2D()
{
	TextLogger::LOG("Deleting grid", LOGGING_DEBUG);
	// We start by deleting the start and end node objects
	delete _startNode;
	delete _endNode;

	TextLogger::LOG("Grid nodes deleted", LOGGING_DEBUG);

	// Delete all chars from the map to prevent a memory leak
	for (int i = 0; i < _height; i++)
	{
		delete[] _map[i];
	}

	delete[] _map;

	TextLogger::LOG("Grid Deleted", LOGGING_DEBUG);
}

/// <summary>
/// Add a new blocked location
/// <summary>
/// <param name="x">The first point along the x axis</param>
/// <param name="y">The first point along the y axis</param>
/// <param name="w">The width the blockage spans across the x axis</param>
/// <param name="h">The width the blockage spans across the y axis</param>
void Grid2D::AddLocation(int x, int y, int w, int h)
{
	//Ensure the blockage is being placed within the map
	if (x > _width || y > _height)
	{
		return;
	}
	//Iterate over relevant rows. Ensure starts counting from 0 or higher
	for (int i = max(0, y); i < min(y + h, (_height)); i++)
	{
		//Iterate over relevant columns. Ensure starts counting from 0 or higher
		for (int j = max(0, x); j < min(x + w, (_width)); j++)
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
void Grid2D::AddStart(int x, int y)
{
	Point2D start;
	start.x = x;
	start.y = y;

	_startNode = new SearchNode(start);
	_map[y][x] = POSITION;
}

/// <summary>
/// Returns an entire grid
/// </summary>
char** Grid2D::GetGrid()
{
	return _map;
}

/// <summary>
/// Returns the size of the grid
/// </summary>
Point2D Grid2D::GridSize()
{
	Point2D ret;
	ret.x = _width;
	ret.y = _height;
	return  ret;
}

/// <summary>
/// Add end and create end node
/// </summary>
/// <param name="x">X position of end</param>
/// <Param name="y">Y position of end</param>
void Grid2D::AddEnd(int x, int y)
{
	Point2D endPt;
	endPt.x = x;
	endPt.y = y;

	_endNode = new SearchNode(endPt);
	_map[y][x] = END;
}

/// <summary>
/// Check the state of a given grid location
/// </summary>
/// <param name="pos">The 2d position on the map</param>
int Grid2D::AtPos(Point2D pos)
{
	// Ensure we are not out of range
	if (0 > pos.x || _width <= pos.x || 0 > pos.y || _height <= pos.y)
	{
		return BLOCKED;
	}
	return _map[pos.y][pos.x];
}

/// <summary>
/// Print a text-representation of the grid
/// </summary>
void Grid2D::PrintMap()
{
	stringstream lSs;
	
	// Create a border
	for (int i = _width+2; i > 0; i--)
	{
		lSs << "-";
	}
	TextLogger::LOG(lSs.str(), LOGGING_DEFAULT);

	for (int i = 0; i < _height; i++)
	{
		lSs.str(string());
		// More borders
		lSs << "|";

		// Text representation of each different position state
		for (int j = 0; j < _width; j++)
		{
			switch (_map[i][j])
			{
				case BLOCKED:
				{
					lSs << "X";
					break;
				}
				case CLEAR:
				{
					lSs << ".";
					break;
				}
				case POSITION:
				{
					lSs << "O";
					break;
				}
				case END:
				{
					lSs << "*";
					break;
				}
				case PATH:
				{
					lSs << "p";
					break;
				}
				case SEARCHED:
				{
					lSs << "s";
					break;
				}
				case QUEUED:
				{
					lSs << "q";
					break;
				}
			}
		}

		// Right side border
		lSs << "|";

		TextLogger::LOG(lSs.str(), LOGGING_DEFAULT);
	}
	lSs.str(string());

	// Borders
	for (int i = _width + 2; i > 0; i--)
	{
		lSs << "-";
	}
	TextLogger::LOG(lSs.str() , LOGGING_DEFAULT);
}

/// <summary>
/// Get the start node of the map
/// </summary>
SearchNode* Grid2D::GetStart()
{
	return _startNode;
}

/// <summary>
/// Get the end node of the map
/// </summary>
SearchNode* Grid2D::GetEnd()
{
	return _endNode;
}

/// <summary>
/// Set a given map position to a specific state using Point2D
/// </summary>
/// <param name="pos">Position to change state</param>
/// <param name="type">State to change position to</param>
void Grid2D::SetPosition(Point2D pos, int type)
{
	// Avoiding out-of-range
	if (0 > pos.x || _width <= pos.x || 0 > pos.y || _height <= pos.y)
	{
		return;
	}

	_map[pos.y][pos.x] = type;
}

/// <summary>
/// Set a given map position to a specific state using integer values
/// </summary>
/// <param name="x">X Position to change state</param>
/// <param name="y">Y Position to change state</param>
/// <param name="type">State to change position to</param>
void Grid2D::SetPosition(int x, int y, int type)
{
	if (0 > x || _width <= x || 0 > y || _height <= y)
	{
		return;
	}

	_map[y][x] = type;
}

/// <summary>
/// Clone this grid to another grid object, as a grid is single use
/// </summary>
/// <param name="newMap">Location to clone map to</param>
void Grid2D::Clone(Grid2D** newMap)
{
	// We need to initialize the map
	*newMap = new Grid2D(_width, _height);

	// Add start and end using the nodes from this map
	(*newMap)->AddStart(_startNode->GetPos().x, _startNode->GetPos().y);
	(*newMap)->AddEnd(_endNode->GetPos().x, _endNode->GetPos().y);

	// Copy all square states
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			(*newMap)->SetPosition(j, i, _map[i][j]);
		}
	}
}