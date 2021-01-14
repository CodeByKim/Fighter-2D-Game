#pragma once
#include "Library.h"
#include "BmpImageData.h"
#include "IRenderable.h"

class Graphics;
class BaseObject;

class Sprite : public IRenderable
{
public:			
	static Sprite*			Create(const wchar_t* fileName, BaseObject* owner, DWORD colorKey = 0x00ffffff);

	Position2D&				GetPivot();	
	void					SetPivot(Position2D pivot);
	void					SetPivot(int x, int y);

	void					OnRender(Graphics* graphic) override;

private:	
	BmpImageData			mBmpImage;
	DWORD					mColorKey;	
	Position2D				mPivot;	
	BaseObject*				mOwner;
	Sprite(BmpImageData data, DWORD colorKey);
	~Sprite();
};