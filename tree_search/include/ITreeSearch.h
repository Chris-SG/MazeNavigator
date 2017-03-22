#pragma once
#include <string>
#include <vector>

#include "Node.h"

class TreeSearch
{
private:
	std::vector<SearchNode> _searchedNodes;
	SearchNode _currentNode;
public:
	virtual std::vector<SearchNode*> Solve(SearchNode* startNode, SearchNode* endNode) = 0;
protected:
	bool AtEnd(SearchNode& endNode) { return _currentNode == endNode; }
};