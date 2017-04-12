#pragma once
#include "ITreeSearch.h"

/// <summary>
/// BreadthFirstSearch is a search algorithm in which a path is
/// expanded on each level prior to going deeeper
/// </summary>
class BreadthFirstSearch : public TreeSearch
{
private:
public:
	BreadthFirstSearch();
	~BreadthFirstSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};