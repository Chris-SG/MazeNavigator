#pragma once
#include <string>
#include <algorithm>
#include <vector>

#include "Node.h"
#include "Grid2D.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

class TreeSearch
{
private:

public:
	virtual std::vector<SearchNode*> Solve(Grid2D* map) = 0;
protected:	
	std::vector<SearchNode*> _searchedNodes;
	std::vector<SearchNode*> _searchStack;
	SearchNode* _currentNode;

	int _directionOrder[4];

	bool AtEnd(SearchNode* endNode) { return _currentNode == endNode; }
	void GetDirectionOrder(Point2D end);
};

void TreeSearch::GetDirectionOrder(Point2D end)
{
	Point2D lStart = _currentNode->GetPos();
	int lX = std::abs(lStart.x + end.x);
	int lY = std::abs(lStart.y + end.y);

	if (lY > lX)
	{
		_directionOrder[0] = DOWN;
		_directionOrder[1] = RIGHT;
		_directionOrder[2] = LEFT;
		_directionOrder[3] = UP;
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}
	else
	{
		_directionOrder[0] = RIGHT;
		_directionOrder[1] = DOWN;
		_directionOrder[2] = UP;
		_directionOrder[3] = LEFT;
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}
}