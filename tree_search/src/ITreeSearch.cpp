#include "../include/ITreeSearch.h"

void TreeSearch::GetDirectionOrder(Point2D end)
{
	Point2D lStart = _currentNode->GetPos();
	int lX = std::abs(lStart.x + end.x);
	int lY = std::abs(lStart.y + end.y);

	if (lY > lX)
	{
		_directionOrder[0] = DOWN;
		_directionOrder[1] = RIGHT;
		_directionOrder[2] = LEFT;
		_directionOrder[3] = UP;
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}
	else
	{
		_directionOrder[0] = RIGHT;
		_directionOrder[1] = DOWN;
		_directionOrder[2] = UP;
		_directionOrder[3] = LEFT;
		if (lStart.y > end.y)
		{
			std::swap(_directionOrder[1], _directionOrder[2]);
		}
		if (lStart.x > end.x)
		{
			std::swap(_directionOrder[0], _directionOrder[3]);
		}
	}
}