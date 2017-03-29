#pragma once

#include <fstream>
#include <string>

#include "Navigator.h"

/// <summary>
/// A block is a closed off location on a map. This struct allows
/// us to pass a block directly to a Navigator to block.
/// </summary>
struct Block{
	int x;
	int y;
	int w;
	int h;
};

class MapParser
{
private:
	std::fstream* _file; //The file which we will read the map from
public:
	MapParser(std::string fileName);
	void ReadFile(Navigator*& to);
};