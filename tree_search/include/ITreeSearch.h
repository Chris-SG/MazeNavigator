#pragma once
#include <algorithm>
#include <vector>

#include "Grid2D.h"

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

/// <summary>
/// Search algorithms are build off the TreeSearch interface
/// </summmary>
class TreeSearch
{
private:

public:
	virtual std::vector<SearchNode*> Solve(Grid2D* map) = 0;

	void DeleteSearchedNodes();
	void DeleteSearchStack();

	void UpdateMap(Grid2D* map);
protected:	
	std::vector<SearchNode*> _searchedNodes; //The nodes that have been searched, to avoid loops
	std::vector<SearchNode*> _searchStack; //The nodes that are still yet to be searched
	std::vector<SearchNode*> _path; //Final path
	SearchNode* _currentNode; //Current node the search is located at

	int _directionOrder[4]; //Used to store the order in which a search is made (for DFS/BFS)

	bool AtEnd(SearchNode* endNode) { return _currentNode == endNode; }
	void GetDirectionOrder(Point2D end);
	void GetNodeToPush(SearchNode*& toPush, int direction, Point2D pos, Grid2D* map);
	void GetPath();
};

