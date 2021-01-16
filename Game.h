#pragma once

#define WINDOWCLASS_NAME L"TCPFighter"
#include "Library.h"

class Graphics;
class GameObject;
class BaseComponent;

class Game
{
public:	
	bool							Create(HINSTANCE hInstance, int nCmdShow);
	void							Run();
	void							Release();
	static Game&					GetInstance();
	
private:	
	void							RegisterWindowClass();
	bool							CreateWindowInstance(int nCmdShow);
	void							CreateComponents();
	void							FrameUpdate();
	static LRESULT CALLBACK			WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Game();
	~Game();

	HINSTANCE						mhInstance;
	HWND							mhWnd;

	Graphics*						mGraphics;	
	std::vector<BaseComponent*>		mComponents;	
	std::vector<GameObject*>		mGameObjects;
};