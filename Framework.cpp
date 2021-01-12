#include "Framework.h"

BOOL Framework::Create(HINSTANCE hInstance, int nCmdShow)
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

VOID Framework::Run()
{
    MSG msg;
    while (TRUE)
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

VOID Framework::Release()
{
    delete m_graphics;
}

Framework& Framework::GetInstance()
{
	static Framework instance;
	return instance;
}

VOID Framework::RegisterWindowClass()
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

BOOL Framework::CreateCreateWindowInstance(int nCmdShow)
{           
    HWND hWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

    if (hWnd == NULL)
    {
        return FALSE;
    }

    m_hWnd = hWnd;

    RECT rectWindow = { 0, 0, 800, 600 };
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

VOID Framework::FrameUpdate()
{
    Sleep(500);

    int x = rand() % 800;
    int y = rand() % 600;

    POINT pos = { x, y };
    WCHAR str[] = L"Hello World";
    m_graphics->DrawString(str, 11, pos);    
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