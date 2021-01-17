#pragma once
#include "Library.h"
#include "BmpImageData.h"
#include "IRenderable.h"

class Graphics;
class GameObject;

class Sprite
{
public:			
	static Sprite*			Create(const wchar_t* fileName, GameObject* owner, DWORD colorKey = 0x00ffffff);	

	Position2D&				GetPivot();	
	void					SetPivot(Position2D pivot);
	void					SetPivot(int x, int y);
	BmpImageData			GetBmpImageData();
	DWORD					GetColorKey();

	Sprite(BmpImageData data, GameObject* owner, DWORD colorKey);
	~Sprite();

private:	
	BmpImageData			mBmpImage;
	DWORD					mColorKey;	
	Position2D				mPivot;	
	GameObject*				mOwner;
};