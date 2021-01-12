#pragma once

#include "Library.h"
#include "Graphics.h"

#define WINDOWCLASS_NAME L"TCPFighter"

class Framework
{
public:	
	bool						Create(HINSTANCE hInstance, int nCmdShow);
	void						Run();
	void						Release();
	static Framework&			GetInstance();

private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;
	Graphics*					m_graphics;

	void						RegisterWindowClass();
	bool						CreateCreateWindowInstance(int nCmdShow);
	void						FrameUpdate();

	static LRESULT CALLBACK		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Framework();
	~Framework();
};