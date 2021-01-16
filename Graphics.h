#pragma once

#include "Library.h"
#include "Screen.h"

class Sprite;

class Graphics
{
public:	
	void Draw(Position2D position, Sprite* sprite);

	Graphics(HWND hWnd, ScreenMemoryBuffer screenBuffer);
	~Graphics();

private:
	HWND						mhWnd;		
	ScreenMemoryBuffer			mScreenBuffer;
};