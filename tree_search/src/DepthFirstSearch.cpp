#include <sstream>

#include "../include/DepthFirstSearch.h"
#include "../include/Timer.h"
#include "../include/TextLogger.h"

using namespace std;

/// <summary>
/// Constructor for DepthFirstSearch
/// </summary>
DepthFirstSearch::DepthFirstSearch()
{

}

DepthFirstSearch::~DepthFirstSearch()
{

}

/// <summary>
/// Attempts to solve the maze using the Depth First Search Algorithm
/// <summary>
/// <param name="map">The map that we wish to solve</param>
std::vector<SearchNode*> DepthFirstSearch::Solve(Grid2D* map)
{
	stringstream lSs;
	TextLogger::LOG("Beginning solve using Depth First Search algorithm", LOGGING_DEFAULT);
	ChronoTimer* timer = new ChronoTimer();
	timer->StartTimer();

	TextLogger::LOG("Detecting map start", LOGGING_DEBUG);
	_currentNode = map->GetStart(); //Get the start point of the map
	SearchNode* lToPush = nullptr; //We don't yet have a node to push

	// Work out what direction we want to be moving
	TextLogger::LOG("Detecting movement order", LOGGING_DEBUG);
	GetDirectionOrder(map->GetEnd()->GetPos());

	// Keep trying until we find the end
	/* consider adding a check so we can't get stuck (will probably crash) */
	while (!(_currentNode->IsEqual(*map->GetEnd())))
	{
		lSs.str(string());
		lSs << "Checking node at location (" << _currentNode->GetPos().x << "," << _currentNode->GetPos().y << ")";
		TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
		// Each node can move to 4 different positions (L/R U/D)
		for (int i = 3; i >= 0; i--)
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
		if (_searchStack.size() == 0)
		{
			TextLogger::LOG("No path exists for maze!", LOGGING_FATAL);
			timer->EndTimer();

			TextLogger::LOG("Completed in " + timer->PrintTime_ms(), LOGGING_DEFAULT);
			_timeTaken = timer->GetTime_ms();
			return _path;
		}
		_currentNode = _searchStack.back(); // And get a new node to visit
		_searchStack.pop_back(); // And remove it from the list of nodes we need to visit
	}

	TextLogger::LOG("Path found!", LOGGING_DEBUG);

	// The start node will return nullptr as the previous node, so we can
	// use this to check if we are back at the start
	GetPath();

	timer->EndTimer();

	TextLogger::LOG("Path found in " + timer->PrintTime_ms(), LOGGING_DEFAULT);
	_timeTaken = timer->GetTime_ms();
	// Return our successful path
	return _path;
}