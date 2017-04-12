#pragma once
#include "AdditionalTypes.h"
#include "Grid2D.h"
#include <vector>

#define IMAGESIZEPERNODE 32

struct colour
{
	int r;
	int g;
	int b;
};

namespace ImageWriter
{
	void WriteImage(std::string fileName, char** map, std::vector<colour>* colours, int x, int y, int pxsize);
}