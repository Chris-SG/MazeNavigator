#pragma once
#include "AdditionalTypes.h"
#include "Grid2D.h"

#define IMAGESIZEPERNODE 12

const int gStart[3] = { 0, 255, 0 }; // Map Start
const int gEnd[3] = { 255, 0, 0 }; // Map end
const int gPath[3] = { 255, 255, 0 }; // Path followed
const int gSearched[3] = { 0, 255, 255 }; // Searched positions
const int gToSearch[3] = { 255, 0, 255 }; // Unsearched positions
const int gOpen[3] = { 255, 255, 255 }; // Open map areas
const int gClosed[3] = { 0, 0, 0 }; // Closed map areas

void WriteImage(std::string fileName, char** map);