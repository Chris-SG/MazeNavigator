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

bool SearchNode::operator==(const SearchNode& otherNode) const
{
	return (otherNode.GetPos().x == _position.x && otherNode.GetPos().y == _position.y);
}

bool SearchNode::operator!=(const SearchNode& otherNode) const
{
	return !(*this == otherNode);
}

int SearchNode::GetDistance_Travelled(const SearchNode& start)
{
	int ret = 0;
	if (*this != start && _previousNode != nullptr)
	{
		ret = 1 + _previousNode->GetDistance_Travelled(start);
	}

	return ret;
}

int SearchNode::GetDistance_Remaining(int endX, int endY)
{
	return (abs(endX - _position.x) + abs(endY - _position.y));
}