#include "../include/Grid2D.h"

#include <algorithm>

using namespace std;

Grid2D::Grid2D(int width, int height)
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

Grid2D::~Grid2D()
{
	delete _startNode;
	delete _endNode;

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
void Grid2D::AddLocation(int x, int y, int w, int h)
{
	//Ensure the blockage is being placed within the map
	if (x > _width || y > _height)
	{
		return;
	}

	//Iterate over relevant rows. Ensure starts counting from 0 or higher
	for (int i = max(0, y); i < min(h, (_height - y)); i++)
	{
		//Iterate over relevant columns. Ensure starts counting from 0 or higher
		for (int j = max(0, x); i < min(w, (_width - x)); i++)
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
	_map[x][y] = POSITION;
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
	_map[x][y] = END;
}

int Grid2D::AtPos(Point2D pos)
{
	if (0 > pos.x || _width < pos.x || 0 > pos.y || _height < pos.y)
	{
		return BLOCKED;
	}
	return _map[pos.x][pos.y];
}

SearchNode* Grid2D::GetStart()
{
	return _startNode;
}

SearchNode* Grid2D::GetEnd()
{
	return _endNode;
}