#pragma once

#include "Node.h"

#include "ITreeSearch.h"

#define CLEAR 0
#define BLOCKED 1
#define POSITION 2
#define END 3

#define COST_UP 1
#define COST_LEFT 1
#define COST_DOWN 1
#define COST_RIGHT 1

class Navigator
{
private:
	int** _map;
	int _width, _height;
	int _posX, _posY;
	int _endX, _endY;

	SearchNode* _startNode;
	SearchNode* _endNode;

public:
	Navigator(int width, int height);
	~Navigator();

	void AddLocation(int x, int y, int w, int h);
	void AddStart(int x, int y);
	void AddEnd(int x, int y);

	void Navigate(TreeSearch& searchModule);
};