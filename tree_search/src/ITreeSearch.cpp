#include <iostream>

#include "../include/ITreeSearch.h"

/// <summary>
/// Get the order of direction to search by
/// <summary>
/// <param name="end">Location of end node</param>
void TreeSearch::GetDirectionOrder(Point2D end)
{
	/******************
	
		This large commented section contains a way to prioritise directions based on the map start and end.
		As the project details stated a search order, it is not in use for this project.
	
	******************/

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

	// We must search UP, then LEFT, then DOWN, then RIGHT
	_directionOrder[0] = UP;
	_directionOrder[1] = LEFT;
	_directionOrder[2] = DOWN;
	_directionOrder[3] = RIGHT;
}

/// <summary>
/// Delete nodes that we have already investigated
/// <summary>
void TreeSearch::DeleteSearchedNodes()
{
	for (int i = _searchedNodes.size()-1; i >= 0; --i)
	{
		delete _searchedNodes.at(i);
	}
}

/// <summary>
/// Delete nodes that we have yet to investigate
/// <summary>
void TreeSearch::DeleteSearchStack()
{
	for (int i = _searchStack.size()-1; i >= 0; --i)
	{
		delete _searchStack.at(i);
	}
}

/// <summary>
/// Update map with new search status
/// <summary>
/// <param name="map">The map we wish to update</param>
void TreeSearch::UpdateMap(Grid2D* map)
{
	for (size_t i = 0; i < _searchedNodes.size(); i++)
	{
		map->SetPosition(_searchedNodes.at(i)->GetPos(), SEARCHED);
	}

	for (size_t i = 0; i < _searchStack.size(); i++)
	{
		map->SetPosition(_searchStack.at(i)->GetPos(), QUEUED);
	}

	for (size_t i = 1; i < _path.size()-1; i++)
	{
		map->SetPosition(_path.at(i)->GetPos(), PATH);
	}
}

/// <summary>
/// Get a node to add to the searchstack based on movement direction
/// <summary>
/// <param name="toPush">A pointer to the node we want to push</param>
/// <param name="direction">Direction we should move the node (L/R/U/D)</param>
/// <param name="pos">Used for the new node position</param>
/// <param name="map">Our map we want to move around on</param>
void TreeSearch::GetNodeToPush(SearchNode*& toPush, int direction, Point2D pos, Grid2D* map)
{
	// Based on the direction provided, we must check if the location in that direction is accessible.
	switch (direction)
	{
	case LEFT:
		pos.x--;
		if (map->AtPos(pos) != BLOCKED)
		{
			toPush = new SearchNode(pos, _currentNode);
		}
		else
			toPush = nullptr;
		break;

	case RIGHT:
		pos.x++;
		if (map->AtPos(pos) != BLOCKED)
		{
			toPush = new SearchNode(pos, _currentNode);
		}
		else 
			toPush = nullptr;
		break;

	case UP:
		pos.y--;
		if (map->AtPos(pos) != BLOCKED)
		{
			toPush = new SearchNode(pos, _currentNode);
		}
		else 
			toPush = nullptr;
		break;

	case DOWN:
		pos.y++;
		if (map->AtPos(pos) != BLOCKED)
		{
			toPush = new SearchNode(pos, _currentNode);
		}
		else
			toPush = nullptr;
		break;
	}
}

/// <summary>
/// Get the entire path of a node from the start position, using traversal.
/// </summary>
void TreeSearch::GetPath()
{
	// nullptr represents the node before the start node
	while (_currentNode != nullptr)
	{
		// We remove our path of nodes from the searched stack for drawing purposes
		for (size_t i = 0; i < _searchedNodes.size(); i++)
		{
			if (_currentNode->IsEqual(*_searchedNodes.at(i)))
			{
				_searchedNodes.erase(_searchedNodes.begin() + i);
			}
		}
		_path.push_back(_currentNode); // add the node to our correct path
		_currentNode = _currentNode->GetPrevious(); // get the previous node in the path
	}
}

/// <summary>
/// Return the time taken in ms to find a path
/// </summary>
int TreeSearch::TimeTaken()
{
	return static_cast<int>(_timeTaken);
}