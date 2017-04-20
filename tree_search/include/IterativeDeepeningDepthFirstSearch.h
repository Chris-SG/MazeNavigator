#pragma once
#include "ITreeSearch.h"

/// <summary>
/// DepthFirstSearch is a search algorithm in which a node is followed
/// all the way to the end before following another node's path
/// </summary>
class IterativeDeepeningDepthFirstSearch : public TreeSearch
{
private:
	std::vector<SearchNode*> DLS(Grid2D* map, int depth);

	SearchNode* _startNode;
public:
	IterativeDeepeningDepthFirstSearch();
	~IterativeDeepeningDepthFirstSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};