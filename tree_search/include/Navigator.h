#pragma once

#include "Node.h"
#include "Grid2D.h"

#include "ITreeSearch.h"

#define COST_UP 1
#define COST_LEFT 1
#define COST_DOWN 1
#define COST_RIGHT 1

class Navigator
{
private:
	Grid2D* _map;

public:
	Navigator(int width, int height);
	~Navigator();

	void Navigate(TreeSearch& searchModule);
};