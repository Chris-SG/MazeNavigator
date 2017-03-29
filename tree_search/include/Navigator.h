#pragma once

#include "ITreeSearch.h"

// These movement costs are to be used in Greedy BFS & A*
#define COST_UP 1
#define COST_LEFT 1
#define COST_DOWN 1
#define COST_RIGHT 1

/// <summary>
/// A navigator is simply an entry point to a ITreeSearch module.
/// Also used to initiate the map.
/// </summary>
class Navigator
{
private:
	Grid2D* _map; //The map we are searching through

public:
	Navigator(int width, int height);
	~Navigator();

	Grid2D* GetMap();

	void Navigate(TreeSearch* searchModule);
};