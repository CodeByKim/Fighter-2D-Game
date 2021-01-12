#pragma once

#include "Library.h"

#define WINDOWCLASS_NAME L"TCPFighter"

class Framework
{
public:	
	BOOL						Create(HINSTANCE hInstance, int nCmdShow);
	VOID						Run();
	VOID						Release();
	static Framework&			GetInstance();

private:
	HINSTANCE					m_hInstance;
	HWND						m_hWnd;

	VOID						RegisterWindowClass();
	BOOL						CreateCreateWindowInstance(int nCmdShow);
	VOID						FrameUpdate();

	static LRESULT CALLBACK		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Framework();
	~Framework();
};