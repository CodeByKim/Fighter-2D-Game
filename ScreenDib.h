#pragma once
#include "Library.h"

class ScreenDib
{
public:
	ScreenDib(int width, int height, int colorBit);
	~ScreenDib();

	void CreateDibBuffer(int width, int height, int colorBit);
	void ReleaseDibBuffer();
	void DrawBuffer(HWND hWnd, int x, int y);

	BYTE* GetDibBuffer();
	int GetWidth();
	int GetHeight();
	int GetPitch();
		
private:
	BITMAPINFO m_stDibInfo;
	BYTE* m_bypBuffer;
	int m_iWidth;
	int m_iHeight;
	int m_iPitch;
	int m_iColorBit;
	int m_iBufferSize;
};

