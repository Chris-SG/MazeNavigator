#include "../include/Grid2D.h"
#include "../include/TextLogger.h"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

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

Grid2D::~Grid2D()
{
	cout << "Deleting grid." << endl;
	delete _startNode;
	delete _endNode;

	cout << "Grid nodes deleted." << endl;

	for (int i = 0; i < _height; i++)
	{
		delete[] _map[i];
	}

	delete[] _map;

	cout << "Grid deleted." << endl;
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

char** Grid2D::GetGrid()
{
	return _map;
}

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

int Grid2D::AtPos(Point2D pos)
{
	if (0 > pos.x || _width <= pos.x || 0 > pos.y || _height <= pos.y)
	{
		return BLOCKED;
	}
	return _map[pos.y][pos.x];
}

void Grid2D::PrintMap()
{
	for (int i = _width+2; i > 0; i--)
	{
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < _height; i++)
	{
		cout << "|";
		for (int j = 0; j < _width; j++)
		{
			switch (_map[i][j])
			{
				case BLOCKED:
				{
					cout << "X";
					break;
				}
				case CLEAR:
				{
					cout << ".";
					break;
				}
				case POSITION:
				{
					cout << "O";
					break;
				}
				case END:
				{
					cout << "*";
					break;
				}
				case PATH:
				{
					cout << "p";
					break;
				}
				case SEARCHED:
				{
					cout << "s";
					break;
				}
				case QUEUED:
				{
					cout << "q";
					break;
				}
			}
		}
		cout << "|";

		cout << endl;
	}

	for (int i = _width + 2; i > 0; i--)
	{
		cout << "-";
	}
	cout << endl;
}



SearchNode* Grid2D::GetStart()
{
	return _startNode;
}

SearchNode* Grid2D::GetEnd()
{
	return _endNode;
}

void Grid2D::SetPosition(Point2D pos, int type)
{
	if (0 > pos.x || _width <= pos.x || 0 > pos.y || _height <= pos.y)
	{
		return;
	}

	_map[pos.y][pos.x] = type;
}