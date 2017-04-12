#include "../include/Image.h"

#include <fstream>

#include <iostream>

using namespace std;

/// <summary>
/// Used to write an image to the disk
/// Intended to draw out a solved map
/// </summary>
/// <param name="filename">File to write</param>
/// <param name="map">A 2d map grid</param>
void ImageWriter::WriteImage(std::string fileName, char** map, vector<colour>* colours, int x, int y)
{
	fstream* lFile = new fstream(fileName, fstream::out, fstream::binary);

	char lPadding = (x * 3) % 4;
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
	unsigned char lInfoHeader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, (unsigned char)(IMAGESIZEPERNODE), (unsigned char)(IMAGESIZEPERNODE >> 8), 0,0,0,0, 0,0,0,0, 4,0,0,0, 4,0,0,0, 0,0,0,0, 0,0,0,0 };

	lInfoHeader[4] = (unsigned char)(x);
	lInfoHeader[5] = (unsigned char)(x >> 8);
	lInfoHeader[6] = (unsigned char)(x >> 16);
	lInfoHeader[7] = (unsigned char)(x >> 24);

	lInfoHeader[8] = (unsigned char)(y);
	lInfoHeader[9] = (unsigned char)(y >> 8);
	lInfoHeader[10] = (unsigned char)(y >> 16);
	lInfoHeader[11] = (unsigned char)(y >> 24);

	// File size calculated by size of header, info header, and 3 bytes per pixel (rgb)
	int lBitmapSize = 3 * x*y + (lPadding * y);
	int lFilesize = 14 + 40 + lBitmapSize;

	cout << "filesize " << lFilesize << " and bitmap size " << lBitmapSize;

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

	cout << "Writing image file to " << fileName << "." << endl;
	
	lFile->write(reinterpret_cast<char*>(&lHeader), sizeof(lHeader));
	cout << "Wrote header" << endl;
	lFile->write(reinterpret_cast<char*>(&lInfoHeader), sizeof(lInfoHeader));
	cout << "Wrote info header" << endl;

	unsigned char lToWrite[3] = { 0,0,0 };
	char lZero = 0;
	// Change this to using a colour list passed to the function, allows use in more than just this program :)
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			colour lColour = colours->at(map[i][j]);
			lToWrite[0] = lColour.b;
			lToWrite[1] = lColour.g;
			lToWrite[2] = lColour.r;

			lFile->write(reinterpret_cast<char*>(&lToWrite), sizeof(lToWrite));
		}

		for (int j = 0; j < lPadding; j++)
		{
			cout << "writing padding" << endl;
			lFile->write(&lZero, sizeof(char));
		}
	}

	cout << "Wrote colours" << endl;

	lFile->close();
}