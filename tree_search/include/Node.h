#pragma once
#include <string>

#include "AdditionalTypes.h"

/// <summary>
/// A search node is a location on the map with information.
/// It allows us to backtrack and check distances from the
/// start and end of the map.
/// </summary>
class SearchNode
{
private:
	std::string _name; //Name of the node, UNUSED
	Point2D _position; //The position of the node on the map
	SearchNode* _previousNode; //The node that moved to this position
public:
	SearchNode(Point2D position);
	SearchNode(Point2D position, SearchNode* previousNode);

	~SearchNode();

	Point2D GetPos() const { return _position; };
	int GetDistance_Travelled(const SearchNode& start);
	int GetDistance_Remaining(int endX, int endY);

	SearchNode* GetPrevious() { return _previousNode; };

	bool operator==(const SearchNode& otherNode);
	bool operator!=(const SearchNode& otherNode);
	bool IsEqual(const SearchNode& otherNode);
};