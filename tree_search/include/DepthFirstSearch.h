#pragma once
#include "ITreeSearch.h"

/// <summary>
/// DepthFirstSearch is a search algorithm in which a node is followed
/// all the way to the end before following another node's path
/// </summary>
class DepthFirstSearch : public TreeSearch
{
private:
public:
	DepthFirstSearch();
	~DepthFirstSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};