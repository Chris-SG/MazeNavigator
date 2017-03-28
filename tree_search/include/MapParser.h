#pragma once

#include <fstream>
#include <string>

#include "Navigator.h"

struct Block{
	int x;
	int y;
	int w;
	int h;
};

class MapParser
{
private:
	std::fstream* _file;
public:
	MapParser(std::string fileName);
	void ReadFile(Navigator* to);
};