#pragma comment(lib, "winmm.lib")

//정리대상
#include "ScreenDib.h"
#include "SpriteDib.h"

#include "Game.h"
#include "Sprite.h"

#include "InputComponent.h"
#include "ObjectComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Graphics.h"

CSpriteDib g_SpriteDib(2, 0x00ffffff);
ScreenDib g_Screen(640, 480, 32);

bool Game::Create(HINSTANCE hInstance, int nCmdShow)
{
    mhInstance = hInstance;

    timeBeginPeriod(1);

    //wchar_t playerSpriteName[] = L"Stand_R_01.bmp";
    //wchar_t mapSpriteName[] = L"Map.bmp";

    //g_SpriteDib.LoadDibSprite(0, mapSpriteName, 0, 0);
    //g_SpriteDib.LoadDibSprite(1, playerSpriteName, 71, 90);

    RegisterWindowClass();
    
    if (CreateWindowInstance(nCmdShow))
    {        
        CreateComponents();

        //테스트코드, 일단 테스트로 오브젝트 하나 넣어놓는다.
        
        mGameObjects.push_back(new GameObject(L"Map.bmp"));        
        mGameObjects.push_back(new GameObject(L"Test.bmp"));

        return TRUE;
    }

    return FALSE;
}

void Game::Run()
{
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            FrameUpdate();
        }
    }
}

void Game::Release()
{
    delete mGraphics;

    timeEndPeriod(1);
}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Game::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = mhInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = WINDOWCLASS_NAME;
    wcex.hIconSm = NULL;

    RegisterClassExW(&wcex);
}

bool Game::CreateWindowInstance(int nCmdShow)
{           
    HWND hWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mhInstance, nullptr);

    if (hWnd == nullptr)
    {
        return false;
    }

    mhWnd = hWnd;

    RECT rectWindow = { 0, 0, 640, 480 };
    AdjustWindowRect(&rectWindow, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(hWnd, 
                HWND_TOPMOST, 
                100, 
                100, 
                rectWindow.right - rectWindow.left, 
                rectWindow.bottom - rectWindow.top, 
                SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return true;
}

void Game::CreateComponents()
{
    mComponents.clear();
    mComponents.reserve(4);     //컴포넌트 갯수는 일단 4개

    mComponents.push_back(new InputComponent());
    mComponents.push_back(new ObjectComponent());
    mComponents.push_back(new CollisionComponent());
    mComponents.push_back(new RenderComponent(mhWnd));
}

std::list<int> fpsQueue;
void Game::FrameUpdate()
{            
    int startTime = timeGetTime();
    
    for (auto iter = mComponents.begin() ; iter != mComponents.end() ; ++iter)
    {
        (*iter)->Execute(mGameObjects);
    }    

    //sleepTime 하드코딩.. 수정해야 함
    int spendTime = timeGetTime() - startTime;        
    
    WCHAR str2[32];
    wsprintf(str2, L"spendTime : %d\n", spendTime);       //21ms 소모되면 47프레임이 나오네...            
    OutputDebugString(str2);
    Sleep(20 - spendTime);

    int endTime = timeGetTime();
    int fps = (1000 / (endTime - startTime));

    fpsQueue.push_back(fps);

    if (fpsQueue.size() >= 30)
    {
        int sum = 0;   
        for (auto iter = fpsQueue.begin(); iter != fpsQueue.end(); ++iter)
        {
            sum += *iter;
        }

        fpsQueue.erase(fpsQueue.begin());
        fps = sum / 30;
    }

    WCHAR str[32];    
    wsprintf(str, L"Logic Frame : %d\n", fps);       //21ms 소모되면 47프레임이 나오네...    
    SetWindowText(mhWnd, str);    
    //OutputDebugString(str);
}

LRESULT CALLBACK Game::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {        
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        //BitmapDraw(hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

Game::Game()
    : mhInstance(nullptr), mhWnd(nullptr), mGraphics(nullptr)
{
}

Game::~Game()
{

}