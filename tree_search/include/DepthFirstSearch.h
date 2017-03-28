#pragma once
#include "ITreeSearch.h"

class DepthFirstSearch : public TreeSearch
{
private:
public:
	DepthFirstSearch();
	virtual std::vector<SearchNode*> Solve(Grid2D* map);
};