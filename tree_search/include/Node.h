#pragma once
#include <string>

#include "MapParser.h"

class SearchNode
{
private:
	std::string _name;
	Point2D _position;
	SearchNode* _previousNode;
public:
	SearchNode(Point2D position);
	SearchNode(Point2D position, SearchNode* previousNode);

	~SearchNode();

	Point2D GetPos() const { return _position; };
	int GetDistance_Travelled(const SearchNode& start);
	int GetDistance_Remaining(int endX, int endY);

	bool operator==(const SearchNode& otherNode) const;
	bool operator!=(const SearchNode& otherNode) const;
};