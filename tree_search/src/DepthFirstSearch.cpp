#include "../include/DepthFirstSearch.h"
#include <iostream>
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
	_currentNode = map->GetStart(); //Get the start point of the map
	SearchNode* lToPush = nullptr; //We don't yet have a node to push

	// Work out what direction we want to be moving
	GetDirectionOrder(map->GetEnd()->GetPos());

	// Keep trying until we find the end
	/* consider adding a check so we can't get stuck (will probably crash) */
	while (_currentNode != map->GetEnd())
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
					if (lToPush == _searchedNodes[i])
					{
						// We don't want to visit it again, so delete the node
						cout << "We have already visited this node!" << endl;
						lVisited = true;
						delete lToPush;
						break;
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

		cout << "Searched " << _searchedNodes.size() << ". List to visit has " << _searchStack.size() << endl;
	
		_searchedNodes.push_back(_currentNode); // We can add our current node to the list of nodes we have searched
		_currentNode = _searchStack.back(); // And get a new node to visit
		_searchStack.pop_back(); // And remove it from the list of nodes we need to visit
	}

	vector<SearchNode*> lPath; //This will hold the full maze path

	// The start node will return nullptr as the previous node, so we can
	// use this to check if we are back at the start
	while (_currentNode != nullptr)
	{
		lPath.push_back(_currentNode); // add the node to our correct path
		_currentNode = _currentNode->GetPrevious(); // get the previous node in the path
	}

	// We need to delete all our unused nodes
	// Will need to add a check so we don't delete our lPath nodes
	for (int i = 0; i < _searchedNodes.size(); i++)
	{
		delete _searchedNodes[i]; //Delete node
	}
	_searchedNodes.clear(); //Clear vector

	/*
	/// Still need to delete searchStack
	*/

	// Return our successful path
	return lPath;
}