#pragma once
#include <algorithm>
#include <vector>

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

