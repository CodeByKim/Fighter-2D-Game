#pragma once

#include "Library.h"
#include "BaseComponent.h"

class Graphics;
class IRenderable;

struct ScreenSize
{
	int width;
	int height;
};

class RenderComponent : public BaseComponent
{
public:
	void Execute() override;	

	RenderComponent(int width = 640, int height = 480, int colorBit = 32);
	~RenderComponent();
	void Register(IRenderable* object)
	{
		mRenderObject = object;
	}

	void SetGraphic(Graphics* graphics)
	{
		mGraphics = graphics;
	}		

private:
	void CreateDibBuffer(int width, int height, int colorBit);
	void ReleaseDibBuffer();

	Graphics* mGraphics;
	BITMAPINFO mDibInfo;	
	ScreenSize mScreenSize;
	HDC mDC;
	int mPitch;
	int mColorBit;

	BYTE* mMemoryBuffer;
	int mBufferSize;

	IRenderable* mRenderObject;
};

