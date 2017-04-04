#pragma once
#include "ITreeSearch.h"

/// <summary>
/// BreadthFirstSearch is a search algorithm in which a node is followed
/// all the way to the end before following another node's path
/// </summary>
class BreadthFirstSearch : public TreeSearch
{
private:
public:
	BreadthFirstSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};