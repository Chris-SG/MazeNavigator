#include <sstream>
#include <iostream>

#include "../include/IterativeDeepeningDepthFirstSearch.h"
#include "../include/Timer.h"
#include "../include/TextLogger.h"

using namespace std;

/// <summary>
/// Constructor for DepthFirstSearch
/// </summary>
IterativeDeepeningDepthFirstSearch::IterativeDeepeningDepthFirstSearch()
{

}

IterativeDeepeningDepthFirstSearch::~IterativeDeepeningDepthFirstSearch()
{

}

/// <summary>
/// Attempts to solve the maze using the Iterative Deepening Depth First Search Algorithm
/// <summary>
/// <param name="map">The map that we wish to solve</param>
vector<SearchNode*> IterativeDeepeningDepthFirstSearch::Solve(Grid2D* map)
{
	stringstream lSs;
	TextLogger::LOG("Beginning solve using Iterative Deepening Depth First Search algorithm", LOGGING_DEFAULT);
	ChronoTimer* timer = new ChronoTimer();
	timer->StartTimer();

	TextLogger::LOG("Detecting map start", LOGGING_DEBUG);
	_startNode = map->GetStart(); //Get the start point of the map

	vector<SearchNode*> lPath;
	int lDepth = 1; 
	bool lSearching = true;
	while (lSearching)
	{
		_currentNode = _startNode;
		lPath.clear();
		lPath = DLS(map, lDepth);

		cout << "size " << lPath.size() << endl;
		if (lPath.size() == lDepth+1)
		{
			lSs.str(string());
			lSs << "Depth " << lPath.size();
			TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
			if (!(lPath[lDepth]->IsEqual(*map->GetEnd())))
			{
				lSearching = true;
				for (int i = _searchedNodes.size()-1; i > 0; i--)
				{
					delete _searchedNodes[i];
				}

				_searchedNodes.resize(0);
			}
			else
			{
				lSearching = false;
			}
		}
		else
		{
			lSearching = false;
			TextLogger::LOG("No path exists for maze!", LOGGING_FATAL);
		}

		lDepth++;
	}

	timer->EndTimer();

	TextLogger::LOG("Completed in " + timer->PrintTime_ms(), LOGGING_DEFAULT);
	_timeTaken = timer->GetTime_ms();
	return  lPath;
}

/// <summary>
/// Navigate maze using DFS to a set length
/// </summary>
vector<SearchNode*> IterativeDeepeningDepthFirstSearch::DLS(Grid2D* map, int depth)
{
	stringstream lSs;
	SearchNode* lToPush;
	int lLongestPath;
	_path.clear();

	GetDirectionOrder(map->GetEnd()->GetPos());

	while (!(_currentNode->IsEqual(*map->GetEnd())))
	{
		if (_currentNode->GetDistance_Travelled() < depth)
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
					TextLogger::LOG("Checking new node", LOGGING_DEBUG);
					bool lVisited = false;
					SearchNode* lPrev = _currentNode->GetPrevious();

					while (lPrev != nullptr)
					{
						if (lToPush->IsEqual(*lPrev))
						{
							TextLogger::LOG("Checked node has been visited", LOGGING_DEBUG);
							lVisited = true;
							delete lToPush;
							break;
						}
						lPrev = lPrev->GetPrevious();
					}

					// If we haven't visited the node
					if (!lVisited)
					{
						// Add it to our list of must-visit nodes
						lSs.str(string());
						lSs << "Search stack size: " << _searchStack.size();
						TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
						_searchStack.push_back(lToPush);
					}
				}
			}
		}

		lLongestPath = max(lLongestPath, _currentNode->GetDistance_Travelled());


		_searchedNodes.push_back(_currentNode); // We can add our current node to the list of nodes we have searched
		if (_searchStack.size() == 0)
		{
			lSs.str(string());
			lSs << "Search stack empty: " << _searchStack.size() << " and path size is currently " << _path.size();
			TextLogger::LOG(lSs.str(), LOGGING_DEBUG);
			GetPath();
			if (_path.size() < lLongestPath)
			{
				_path.resize(lLongestPath);
			}

			//_path.resize(lLongestPath);

			return _path;
		}
		_currentNode = _searchStack.back(); // And get a new node to visit
		_searchStack.pop_back(); // And remove it from the list of nodes we need to visit
	}

	GetPath();

	return _path;
}