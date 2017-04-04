#include "../include/DepthFirstSearch.h"
#include <iostream>
#include "../include/Timer.h"
using namespace std;

/// <summary>
/// Constructor for DepthFirstSearch
/// </summary>
DepthFirstSearch::DepthFirstSearch()
{

}

/// <summary>
/// Attempts to solve the maze using the Depth First Search Algorithm
/// <summary>
/// <param name="map">The map that we wish to solve</param>
std::vector<SearchNode*> DepthFirstSearch::Solve(Grid2D* map)
{
	ChronoTimer* timer = new ChronoTimer();
	timer->StartTimer();

	_currentNode = map->GetStart(); //Get the start point of the map
	SearchNode* lToPush = nullptr; //We don't yet have a node to push

	// Work out what direction we want to be moving
	GetDirectionOrder(map->GetEnd()->GetPos());

	// Keep trying until we find the end
	/* consider adding a check so we can't get stuck (will probably crash) */
	while (!(_currentNode->IsEqual(*map->GetEnd())))
	{
		cout << "At node position: " << _currentNode->GetPos().x << "," << _currentNode->GetPos().y << endl;
		// Each node can move to 4 different positions (L/R U/D)
		for (int i = 3; i >= 0; i--)
		{
			Point2D lPos = _currentNode->GetPos(); //Store the postion of our current node

			// Switch depending on which direction we go
			// Creates a node at the new postion if it is not BLOCKED
			switch (_directionOrder[i])
			{
			case LEFT:
				lPos.x--;
				if (map->AtPos(lPos) != BLOCKED)
				{
					lToPush = new SearchNode(lPos, _currentNode);
					cout << "Left was " << i << endl;
				}
				else
				{
					lToPush = nullptr;
				}
				break;
			case RIGHT:	
				lPos.x++;
				if (map->AtPos(lPos) != BLOCKED)
				{
					lToPush = new SearchNode(lPos, _currentNode);
					cout << "Right was " << i << endl;
				}
				else
				{
					lToPush = nullptr;
				}
				break;
			case UP:
				lPos.y--;
				if (map->AtPos(lPos) != BLOCKED)
				{
					lToPush = new SearchNode(lPos, _currentNode);
					cout << "Up was " << i << endl;
				}
				else
				{
					lToPush = nullptr;
				}
				break;
			case DOWN:
				lPos.y++;
				if (map->AtPos(lPos) != BLOCKED)
				{
					lToPush = new SearchNode(lPos, _currentNode);
					cout << "Down was " << i << endl;
				}
				else
				{
					lToPush = nullptr;
				}
				break;
			}
		
			// We don't want to visit nullptr so skip if we have one
			if (lToPush != nullptr)
			{
				bool lVisited = false;
				// Iterate over all our visited nodes
				// Perhaps use an iterator instead to improve performance on large maps
				for (int i = 0; i < _searchedNodes.size(); i++)
				{
					// If we have already visited the node before...
					if (_searchedNodes[i]->IsEqual(*lToPush))
					{
						// We don't want to visit it again, so delete the node
						lVisited = true;
						delete lToPush;
						break;
					}
				}

				// Also check if we plan to visit the node.
				if (!lVisited)
				{
					for (int i = 0; i < _searchStack.size(); i++)
					{
						if (_searchStack[i]->IsEqual(*lToPush))
						{
							lVisited = true;
							delete lToPush;
							break;
						}
					}
				}

				// If we haven't visited the node
				if (!lVisited)
				{
					// Add it to our list of must-visit nodes
					cout << "Add node to stack!" << endl;
					_searchStack.push_back(lToPush);
				}
			}
		}
	
		_searchedNodes.push_back(_currentNode); // We can add our current node to the list of nodes we have searched
		_currentNode = _searchStack.back(); // And get a new node to visit
		_searchStack.pop_back(); // And remove it from the list of nodes we need to visit
	}

	cout << "Path found!" << endl;

	// The start node will return nullptr as the previous node, so we can
	// use this to check if we are back at the start
	while (_currentNode != nullptr)
	{
		for (int i = 0; i < _searchedNodes.size(); i++)
		{
			if (_currentNode->IsEqual(*_searchedNodes.at(i)))
			{
				cout << "Removed a node" << endl;
				_searchedNodes.erase(_searchedNodes.begin() + i);
			}
		}
		_path.push_back(_currentNode); // add the node to our correct path
		_currentNode = _currentNode->GetPrevious(); // get the previous node in the path
	}
	cout << "a" << endl;

	cout << "Path added" << endl;

	timer->EndTimer();
	cout << "Path found in " << timer->PrintTime_ms() << "." << endl;

	// Return our successful path
	return _path;
}