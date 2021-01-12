#pragma once

#include "Library.h"

class Graphics
{
public:
	
	VOID					DrawString(wchar_t* str, int strLength, POINT position);
	Graphics(HWND hWnd);
	~Graphics();

private:
	HWND	m_hWnd;
	HDC		m_hDC;
};

