#include "framework.h"
#include <cstdio>

class Singleton
{
public:
    static Singleton& GetInstance()
    {
        static Singleton instance;
        return instance;
    }

    void Print(HDC dc)
    {
        TextOut(dc, 0, 0, L"Hello World", 11);
    }

private:
    Singleton() {}
};

#define WINDOWCLASS_NAME L"TCPFighter"

ATOM                RegisterWindowClass(HINSTANCE hInstance);
VOID                CreateWindowInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
VOID                BitmapDraw(HDC hDC);
VOID                Update();

HINSTANCE hInst;
HDC g_hDc;
HWND g_hWnd;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    RegisterWindowClass(hInstance);
    CreateWindowInstance(hInstance, nCmdShow);
    
    g_hDc = GetDC(g_hWnd);

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
        else    //윈도우 데드 타임
        {
            Update();
        }
    }

    ReleaseDC(g_hWnd, g_hDc);
    return (int) msg.wParam;
}

VOID Update()
{
    Singleton::GetInstance().Print(g_hDc);
}

ATOM RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = WINDOWCLASS_NAME;
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}

VOID CreateWindowInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(WINDOWCLASS_NAME, WINDOWCLASS_NAME, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   g_hWnd = hWnd;

   RECT rc = { 0, 0, 800, 600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
   
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {    
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            BitmapDraw(hdc);
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

VOID BitmapDraw(HDC hDC)
{
    HANDLE	hFile;
    DWORD	dwRead;
    int		iPitch;
    int		iImageSize;
    BYTE* bypImage;

    BITMAPFILEHEADER	stFileHeader;
    BITMAPINFOHEADER	stInfoHeader;

    WCHAR	szFileName[] = L"procademy.bmp";

    FILE* pFile = NULL;
    _wfopen_s(&pFile, szFileName, L"rb");
    if (pFile == NULL) return;

    dwRead = fread(&stFileHeader, sizeof(stFileHeader), 1, pFile);

    if (dwRead != 1)
        MessageBox(NULL, L"파일 헤더읽기 에러", L"dd", MB_OK);
    dwRead = fread(&stInfoHeader, sizeof(stInfoHeader), 1, pFile);
    if (dwRead != 1)
        MessageBox(NULL, L"인포 헤더읽기 에러", L"dd", MB_OK);

    iPitch = ((stInfoHeader.biWidth * (stInfoHeader.biBitCount / 8)) + 3) & ~3;
    iImageSize = iPitch * stInfoHeader.biHeight;

    bypImage = (BYTE*)malloc(iImageSize);
    fread(bypImage, iImageSize, 1, pFile);
    fclose(pFile);

    StretchDIBits(hDC, 0, 0, stInfoHeader.biWidth, stInfoHeader.biHeight, 0, 0,
        stInfoHeader.biWidth, stInfoHeader.biHeight, bypImage, (BITMAPINFO*)&stInfoHeader, DIB_RGB_COLORS, SRCCOPY);

    free(bypImage);
}