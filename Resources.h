#pragma once

#include "Library.h"

struct BmpImageData
{
	BYTE* image; 
	int width;
	int height;
	int pitch;
};

class Resources
{
public:
	bool LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName, int iCenterPointX, int iCenterPointY);

	static Resources& GetInstance();
};