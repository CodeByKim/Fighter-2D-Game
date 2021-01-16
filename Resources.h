#pragma once

#include "Library.h"
struct BmpImageData;

class Resources
{
public:
	void LoadSprite(const wchar_t* path, Position2D pivot);
	std::vector<BmpImageData>* GetSprites(std::wstring_view name);
	static Resources& GetInstance();

private:
	bool LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName);

	std::unordered_map<std::wstring, std::vector<BmpImageData>*> mSprites;
};