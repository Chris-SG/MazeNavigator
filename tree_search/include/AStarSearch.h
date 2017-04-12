#pragma once
#include "ITreeSearch.h"

/// <summary>
/// GreedyBestFirstSearch is a search algorithm in which a node is
/// chosen based on the remaining distance to the goal
/// </summary>
class AStarSearch : public TreeSearch
{
private:
public:
	AStarSearch();
	~AStarSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};