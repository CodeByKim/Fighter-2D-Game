#pragma once
#include "Library.h"
#include "BmpImageData.h"

class Sprite
{
public:			
	static Sprite*			Create(const wchar_t* fileName, DWORD colorKey = 0x00ffffff);

	Position2D&				GetPivot();	
	void					SetPivot(Position2D pivot);
	void					SetPivot(int x, int y);

private:	
	BmpImageData			mBmpImage;
	DWORD					mColorKey;	
	Position2D				mPivot;	

	Sprite(BmpImageData data, DWORD colorKey);
	~Sprite();
};