#pragma comment(lib, "winmm.lib")

#include "Game.h"
#include "ScreenDib.h"
#include "Sprite.h"

CSpriteDib g_SpriteDib(2, 0x00ffffff);
ScreenDib g_Screen(640, 480, 32);

bool Game::Create(HINSTANCE hInstance, int nCmdShow)
{
    m_hInstance = hInstance;

    timeBeginPeriod(1);
    wchar_t playerSpriteName[] = L"Stand_R_01.bmp";
    wchar_t mapSpriteName[] = L"Map.bmp";

    g_SpriteDib.LoadDibSprite(0, mapSpriteName, 0, 0);
    g_SpriteDib.LoadDibSprite(1, playerSpriteName, 71, 90);


    RegisterWindowClass();
    
    if (CreateCreateWindowInstance(nCmdShow))
    {
        m_graphics = new Graphics(m_hWnd);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
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
    delete m_graphics;

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
    wcex.hInstance = m_hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = WINDOWCLASS_NAME;
    wcex.hIconSm = NULL;

    RegisterClassExW(&wcex);
}

bool Game::CreateCreateWindowInstance(int nCmdShow)
{           
    HWND hWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

    if (hWnd == NULL)
    {
        return false;
    }

    m_hWnd = hWnd;

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

std::vector<int> fpsQueue;

void Game::FrameUpdate()
{        
    int startTime = timeGetTime();
    
    BYTE* bypDest = g_Screen.GetDibBuffer();
    int iDestWidth = g_Screen.GetWidth();
    int iDestHeight = g_Screen.GetHeight();
    int iDestPitch = g_Screen.GetPitch();

    g_SpriteDib.DrawSprite(0, 0, 0, bypDest, iDestWidth, iDestHeight, iDestPitch);
    g_SpriteDib.DrawSprite(1, 100, 100, bypDest, iDestWidth, iDestHeight, iDestPitch);

    g_Screen.DrawBuffer(m_hWnd, 0, 0);
    
    //sleepTime 하드코딩.. 수정해야 함
    int spendTime = timeGetTime() - startTime;        
    Sleep(20 - spendTime);

    int endTime = timeGetTime();
    int fps = (1000 / (endTime - startTime));

    fpsQueue.push_back(fps);

    if (fpsQueue.size() >= 30)
    {
        int sum = 0;
        for (int i = 0; i < fpsQueue.size(); i++)
        {
            sum += fpsQueue[i];
        }

        fpsQueue.erase(fpsQueue.begin());

        fps = sum / 30;
    }

    WCHAR str[32];    
    wsprintf(str, L"Logic Frame : %d\n", fps);       //21ms 소모되면 47프레임이 나오네...
    SetWindowText(m_hWnd, str);
    OutputDebugString(str);
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
    : m_hInstance(nullptr), m_hWnd(nullptr), m_graphics(nullptr)
{
}

Game::~Game()
{

}