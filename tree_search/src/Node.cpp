#include "../include/Node.h"

/// <summary>
/// Constructor of Node using just a position
/// </summary>
/// <param name="position">Position on map in which node is located</param>
SearchNode::SearchNode(Point2D position)
{
	_position = position;
	// As there is no attached node, we set the previous node to nullptr
	_previousNode = nullptr;
}

/// <summary>
/// Constructor of the Node using a position and previous node
/// <summary>
/// <param name="position">Position on map in which node is located</param>
/// <param name="previous">The previous node moved from</param>
SearchNode::SearchNode(Point2D position, SearchNode* previous)
{
	_position = position;
	_previousNode = previous;
}

SearchNode::~SearchNode()
{

}

#include <iostream>
bool SearchNode::operator==(const SearchNode& otherNode)
{
	return (otherNode.GetPos().x == _position.x && otherNode.GetPos().y == _position.y);
}

bool SearchNode::operator!=(const SearchNode& otherNode)
{
	return !(*this == otherNode);
}

int SearchNode::GetDistance_Travelled()
{
	int ret = 0;
	if (_previousNode != nullptr)
	{
		ret = 1 + _previousNode->GetDistance_Travelled();
	}

	return ret;
}

bool SearchNode::IsEqual(const SearchNode& otherNode)
{
	return *this == otherNode;
}

int SearchNode::GetDistance_Remaining(Point2D end)
{
	return (abs(end.x - _position.x) + abs(end.y - _position.y));
}