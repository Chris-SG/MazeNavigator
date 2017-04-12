#include "../include/Image.h"

#include <fstream>

using namespace std;

/// <summary>
/// Used to write an image to the disk
/// Intended to draw out a solved map
/// </summary>
/// <param name="filename">File to write</param>
/// <param name="map">A 2d map grid</param>
void WriteImage(std::string fileName, char** map)
{
	fstream* lFile = new fstream(fileName, fstream::out);
	int lWidth = sizeof(map) / sizeof(map[0]);
	int lHeight = sizeof(map[0]) / sizeof(map[0][0]);
	// 2 bytes indentify as bmp
	// 4 bytes filesize
	// 2 bytes reserved
	// 2 bytes reserved
	// 4 bytes offset for pixel data
	unsigned char lHeader[14] = { 'B', 'M', 0,0,0,0, 0,0, 0,0, 0,0,0,0 };

	// 4 bytes for size of info header
	// 4 bytes for width
	// 4 bytes for height
	// 2 bytes for colour planes
	// 2 bytes for bits per pixel
	// 4 bytes for compression
	// 4 bytes for size of bitmap data (pixels only)
	// 4 bytes for print resolution
	// 4 bytes for colours in palette
	// 4 bytes for important colours
	unsigned char lInfoHeader[40] = { 28,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, (unsigned char)(IMAGESIZEPERNODE), (unsigned char)(IMAGESIZEPERNODE >> 8), 0,0,0,0, 0,0,0,0, 4,0,0,0, 0,0,0,0, 0,0,0,0 };

	lInfoHeader[4] = (unsigned char)(lWidth);
	lInfoHeader[5] = (unsigned char)(lWidth >> 8);
	lInfoHeader[6] = (unsigned char)(lWidth >> 16);
	lInfoHeader[7] = (unsigned char)(lWidth >> 24);

	lInfoHeader[8] = (unsigned char)(lHeight);
	lInfoHeader[9] = (unsigned char)(lHeight >> 8);
	lInfoHeader[10] = (unsigned char)(lHeight >> 16);
	lInfoHeader[11] = (unsigned char)(lHeight >> 24);

	// File size calculated by size of header, info header, and 3 bytes per pixel (rgb)
	int lBitmapSize = 3 * lWidth*lHeight;
	int lFilesize = 14 + 40 + lBitmapSize;

	// Bitmap must be stored as little-endian
	lInfoHeader[20] = (unsigned char)(lBitmapSize);
	lInfoHeader[21] = (unsigned char)(lBitmapSize>>8);
	lInfoHeader[22] = (unsigned char)(lBitmapSize>>16);
	lInfoHeader[23] = (unsigned char)(lBitmapSize>>24);

	// Filesize must be stored as little-endian
	lHeader[2] = (unsigned char)(lFilesize);
	lHeader[3] = (unsigned char)(lFilesize>>8);
	lHeader[4] = (unsigned char)(lFilesize>>16);
	lHeader[5] = (unsigned char)(lFilesize>>24);

	// OFfset is calculated by size of header and info header
	int lOffset = 14 + 40;
	// Offset must be stored as little-endian
	lHeader[10] = (unsigned char)(lOffset);
	lHeader[11] = (unsigned char)(lOffset>>8);
	lHeader[12] = (unsigned char)(lOffset>>16);
	lHeader[13] = (unsigned char)(lOffset>>24);

	for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
	{
		for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++)
		{
			switch (map[i][j])
			{
			case CLEAR:
				gOpen;
			}
		}
	}
}

#define CLEAR 0
#define BLOCKED 1
#define POSITION 2
#define END 3
#define PATH 6
#define SEARCHED 7
#define QUEUED 8