#include <sstream>

#include "../include/AStarSearch.h"
#include <iostream>
#include "../include/Timer.h"
#include "../include/TextLogger.h"
using namespace std;

/// <summary>
/// Constructor for GreedyBestFirstSearch
/// </summary>
AStarSearch::AStarSearch()
{

}

AStarSearch::~AStarSearch()
{

}

/// <summary>
/// Attempts to solve the maze using the Greedy Best First Search Algorithm
/// <summary>
/// <param name="map">The map that we wish to solve</param>
std::vector<SearchNode*> AStarSearch::Solve(Grid2D* map)
{
	stringstream lSs;
	TextLogger::LOG("Beginning solve using A* algorithm", LOGGING_DEFAULT);
	ChronoTimer* timer = new ChronoTimer();
	timer->StartTimer();

	TextLogger::LOG("Detecting map start", LOGGING_DEBUG);
	_currentNode = map->GetStart(); //Get the start point of the map
	SearchNode* lToPush = nullptr; //We don't yet have a node to push

	// While directions aren't needed for GBFS, we still need 4 directions when discovering nodes
	TextLogger::LOG("Detecting movement order", LOGGING_DEBUG);
	GetDirectionOrder(map->GetEnd()->GetPos());

	TextLogger::LOG("Detecting map end", LOGGING_DEBUG);
	Point2D lEnd = map->GetEnd()->GetPos();

	// Keep trying until we find the end
	/* consider adding a check so we can't get stuck (will probably crash) */
	while (!(_currentNode->IsEqual(*map->GetEnd())))
	{
		lSs.str(string());
		lSs << "Checking node at location (" << _currentNode->GetPos().x << "," << _currentNode->GetPos().y << ")";
		TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
		// Each node can move to 4 different positions (L/R U/D)
		for (size_t i = 0; i < 4; i++)
		{
			Point2D lPos = _currentNode->GetPos(); //Store the postion of our current node

			GetNodeToPush(lToPush, _directionOrder[i], lPos, map); // Get which node we need to add to our vector

			// We don't want to visit nullptr so skip if we have one
			if (lToPush != nullptr)
			{
				bool lVisited = false;
				// Iterate over all our visited nodes
				// Perhaps use an iterator instead to improve performance on large maps
				for (size_t i = 0; i < _searchedNodes.size(); i++)
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
					for (size_t i = 0; i < _searchStack.size(); i++)
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
					_searchStack.push_back(lToPush);
				}
			}
		}

		_searchedNodes.push_back(_currentNode); // We can add our current node to the list of nodes we have searched

		_currentNode = _searchStack.front();

		TextLogger::LOG("Finding next node to search...", LOGGING_DEBUG);
		// Iterate through all the searchable nodes
		for (size_t i = 1; i < _searchStack.size(); i++)
		{
			// Is the node closer to the goal than we are?
			if (_currentNode->GetDistance_Remaining(lEnd) + _currentNode->GetDistance_Travelled() >= _searchStack[i]->GetDistance_Remaining(lEnd) + _searchStack[i]->GetDistance_Travelled())
			{
				TextLogger::LOG("Finding ideal node to search from", LOGGING_DEBUG);
				_currentNode = _searchStack[i];
			}
		}

		// We can remove our next node from the stack
		_searchStack.erase(remove(_searchStack.begin(), _searchStack.end(), _currentNode), _searchStack.end());
	}

	TextLogger::LOG("Path found!", LOGGING_DEBUG);

	GetPath();

	timer->EndTimer();

	TextLogger::LOG("Path found in " + timer->PrintTime_ms(), LOGGING_DEFAULT);
	_timeTaken = timer->GetTime_ms();
	// Return our successful path
	return _path;
}