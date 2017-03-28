#pragma once

#include "Node.h"

#define CLEAR 0
#define BLOCKED 1
#define POSITION 2
#define END 3

class Grid2D
{
private:
	int** _map;
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

	SearchNode* GetStart() { return _startNode; }
	SearchNode* GetEnd() { return _endNode; }
};