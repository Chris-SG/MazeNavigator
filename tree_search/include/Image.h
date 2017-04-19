#pragma once
#include <vector>

#include "AdditionalTypes.h"
#include "Grid2D.h"

#define IMAGESIZEPERNODE 32 //size of each pixel on the image. A smaller value will increase performance

/// <summary>
/// Colour struct holds colour information for our image
/// </summary>
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