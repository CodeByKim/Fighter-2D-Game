#pragma once

#include "Library.h"
#include "BaseComponent.h"
#include "Screen.h"

class Graphics;

class RenderComponent : public BaseComponent
{
public:
	void Execute(std::vector<GameObject*>& gameObjects) override;

	RenderComponent(HWND hWnd, int width = 640, int height = 480, int colorBit = 32);
	~RenderComponent();

private:
	void CreateDibBuffer(int width, int height, int colorBit);
	void ReleaseDibBuffer();

	Graphics* mGraphics;
	BITMAPINFO mDibInfo;	
	HWND mhWnd;
	HDC mDC;
	
	ScreenMemoryBuffer screenBuffer;	
};

