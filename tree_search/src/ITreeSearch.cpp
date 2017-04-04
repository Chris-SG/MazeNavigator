#include "../include/ITreeSearch.h"
#include <iostream>

void TreeSearch::GetDirectionOrder(Point2D end)
{
	/*Point2D lStart = _currentNode->GetPos();
	int lX = std::abs(lStart.x + end.x);
	int lY = std::abs(lStart.y + end.y);

	std::cout << "x is " << lX << " and y is " << lY << std::endl;

	if (lY > lX)
	{
		_directionOrder[0] = DOWN;
		_directionOrder[1] = RIGHT;
		_directionOrder[2] = LEFT;
		_directionOrder[3] = UP;
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}
	else
	{
		_directionOrder[0] = RIGHT;
		_directionOrder[1] = DOWN;
		_directionOrder[2] = UP;
		_directionOrder[3] = LEFT;
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}*/

	_directionOrder[0] = UP;
	_directionOrder[1] = LEFT;
	_directionOrder[2] = DOWN;
	_directionOrder[3] = RIGHT;
}

void TreeSearch::DeleteSearchedNodes()
{
	for (int i = _searchedNodes.size()-1; i >= 0; --i)
	{
		delete _searchedNodes.at(i);
	}
}

void TreeSearch::DeleteSearchStack()
{
	for (int i = _searchStack.size()-1; i >= 0; --i)
	{
		delete _searchStack.at(i);
	}
}

void TreeSearch::UpdateMap(Grid2D* map)
{
	for (int i = 0; i < _searchedNodes.size(); i++)
	{
		map->SetPosition(_searchedNodes.at(i)->GetPos(), SEARCHED);
	}

	for (int i = 0; i < _searchStack.size(); i++)
	{
		map->SetPosition(_searchStack.at(i)->GetPos(), QUEUED);
	}

	for (int i = 0; i < _path.size(); i++)
	{
		map->SetPosition(_path.at(i)->GetPos(), PATH);
	}
}
