#pragma once

#include "Node.h"

#define CLEAR 0
#define BLOCKED 1
#define POSITION 2
#define END 3
#define PATH 4
#define SEARCHED 5
#define QUEUED 6

/// <summary>
/// A Grid2D holds information relating to a provided map, including
/// the layout, the start point, and the end point.
/// </summary>
class Grid2D
{
private:
	char** _map;
	int _width, _height;

	SearchNode* _startNode;
	SearchNode* _endNode;
public:
	Grid2D(int width, int height);
	~Grid2D();

	void AddLocation(int x, int y, int w, int h);
	void AddStart(int x, int y);
	void AddEnd(int x, int y);
	int AtPos(Point2D loc);
	void SetPosition(Point2D loc, int type);

	Point2D GridSize();

	char** GetGrid();

	void PrintMap();

	SearchNode* GetStart();
	SearchNode* GetEnd();
};