#pragma once

#include "Library.h"

class Graphics
{
public:
	
	VOID					DrawString(WCHAR* str, DWORD strLength, POINT position);
	Graphics(HWND hWnd);
	~Graphics();

private:
	HWND	m_hWnd;
	HDC		m_hDC;
};

