#include "../include/DepthFirstSearch.h"

using namespace std;

DepthFirstSearch::DepthFirstSearch()
{

}

std::vector<SearchNode*> DepthFirstSearch::Solve(Grid2D* map)
{
	_currentNode = map->GetStart();
	SearchNode* lToPush = nullptr;

	GetDirectionOrder(map->GetEnd()->GetPos());


	while (_currentNode != map->GetEnd())
	{
		for (int i = 0; i < 4; i++)
		{
			Point2D lPos = _currentNode->GetPos();
			switch (_directionOrder[i])
			{
			case LEFT:
				lPos.x--;
				if (map->AtPos(lPos) != BLOCKED)
				{
					lToPush = new SearchNode(lPos, _currentNode);
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
				}
				else
				{
					lToPush = nullptr;
				}
				break;
			}
		
			if (lToPush != nullptr)
			{
				bool lVisited = false;
				for (int i = 0; i < _searchedNodes.size(); i++)
				{
					if (lToPush == _searchedNodes[i])
					{
						lVisited = true;
						delete lToPush;
						break;
					}
				}

				if (!lVisited)
				{
					_searchStack.push_back(lToPush);
				}
			}
		}
	
		_searchedNodes.push_back(_currentNode);
		_currentNode = _searchStack.back();
		_searchStack.pop_back();
	}

	vector<SearchNode*> lPath;
	while (_currentNode != nullptr)
	{
		lPath.push_back(_currentNode);
		_currentNode = _currentNode->GetPrevious();
	}

	for (int i = 0; i < _searchedNodes.size(); i++)
	{
		delete _searchedNodes[i];
	}
	_searchedNodes.clear();

	return lPath;
}