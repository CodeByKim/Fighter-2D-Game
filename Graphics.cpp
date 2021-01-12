#include "Graphics.h"

VOID Graphics::DrawString(WCHAR* str, DWORD strLength, POINT position)
{
	TextOut(m_hDC, position.x, position.y, str, strLength);
}

Graphics::Graphics(HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
}

Graphics::~Graphics()
{
	ReleaseDC(m_hWnd, m_hDC);
}