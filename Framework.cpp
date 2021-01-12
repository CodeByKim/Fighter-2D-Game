#include "Framework.h"
#include "ScreenDib.h"

ScreenDib g_Screen(640, 480, 32);

bool Framework::Create(HINSTANCE hInstance, int nCmdShow)
{
    m_hInstance = hInstance;

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

void Framework::Run()
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

void Framework::Release()
{
    delete m_graphics;
}

Framework& Framework::GetInstance()
{
	static Framework instance;
	return instance;
}

void Framework::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Framework::WndProc;
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

bool Framework::CreateCreateWindowInstance(int nCmdShow)
{           
    HWND hWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

    if (hWnd == NULL)
    {
        return FALSE;
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

    return TRUE;
}

void Framework::FrameUpdate()
{    
    BYTE* bypDest = g_Screen.GetDibBuffer();
    int iDestWidth = g_Screen.GetWidth();
    int iDestHeight = g_Screen.GetHeight();
    int iDestPitch = g_Screen.GetPitch();
    
    BYTE byGrayColor = 0;
    for (int iCount = 0; iCount < 480; iCount++)
    {
        memset(bypDest, byGrayColor, 640 * 4);
        bypDest += iDestPitch;
        byGrayColor++;
    }
    
    g_Screen.DrawBuffer(m_hWnd, 0, 0);

    /*Sleep(1);
    int x = rand() % 800;
    int y = rand() % 600;

    POINT pos = { x, y };
    wchar_t str[] = L"Hello World";
    m_graphics->DrawString(str, wcslen(str), pos);*/
}

LRESULT CALLBACK Framework::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

Framework::Framework() 
    : m_hInstance(NULL), m_hWnd(NULL)
{
}

Framework::~Framework()
{

}