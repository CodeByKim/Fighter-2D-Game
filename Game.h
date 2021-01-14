#pragma once

#define WINDOWCLASS_NAME L"TCPFighter"
#include "Library.h"

class Graphics;
class RenderComponent;
class GameObject;

class Game
{
public:	
	bool						Create(HINSTANCE hInstance, int nCmdShow);
	void						Run();
	void						Release();
	static Game&				GetInstance();
	RenderComponent* mRenderComponent;

private:	
	void						RegisterWindowClass();
	bool						CreateWindowInstance(int nCmdShow);
	void						FrameUpdate();

	static LRESULT CALLBACK		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Game();
	~Game();

	HINSTANCE					mhInstance;
	HWND						mhWnd;
	Graphics*					mGraphics;
	
	GameObject*					mTestPlayer;
};