#pragma once

#include "Library.h"
struct BmpImageData;

class Resources
{
public:
	bool LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName, int iCenterPointX, int iCenterPointY);

	static Resources& GetInstance();
};