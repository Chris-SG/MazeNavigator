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
/// </summary>
/// <param name="position">Position on map in which node is located</param>
/// <param name="previous">The previous node moved from</param>
SearchNode::SearchNode(Point2D position, SearchNode* previous)
{
	_position = position;
	_previousNode = previous;
}

/// <summary>
/// Destructor of node class
/// </summary>
SearchNode::~SearchNode()
{

}

/// <summary>
/// Comparison operator equals to compare grid position of two nodes
/// </summary>
/// <param name="otherNode">Node to compare against</param>
bool SearchNode::operator==(const SearchNode& otherNode)
{
	return (otherNode.GetPos().x == _position.x && otherNode.GetPos().y == _position.y);
}

/// <summary>
/// Comparison operator not equals to compare grid position of two nodes
/// </summary>
/// <param name="otherNode">Node to compare against</param>
bool SearchNode::operator!=(const SearchNode& otherNode)
{
	return !(*this == otherNode);
}

/// <summary>
/// Gather distance travelled from beginning node
/// </summary>
int SearchNode::GetDistance_Travelled()
{
	int ret = 0;
	// We must keep checking until we are at the first node in the list
	if (_previousNode != nullptr)
	{
		ret = 1 + _previousNode->GetDistance_Travelled();
	}

	return ret;
}

/// <summary>
/// Comparison operator equals for when node is a pointer
/// </summary>
/// <param name="otherNode">Node to compare against</param>
bool SearchNode::IsEqual(const SearchNode& otherNode)
{
	return *this == otherNode;
}

/// <summary>
/// Get minimum distance between node and a given point
/// </summary>
/// <param name="end">Point to compare against</param>
int SearchNode::GetDistance_Remaining(Point2D end)
{
	return (abs(end.x - _position.x) + abs(end.y - _position.y));
}