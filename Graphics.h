#pragma once

#include "Library.h"

class Graphics
{
public:	
	void DrawSprite(Position2D position);

	Graphics(HWND hWnd);
	~Graphics();
	HDC							m_hDC;

private:
	HWND						m_hWnd;	
};