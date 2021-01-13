#include <cstdio>

#include "Game.h"
#include "Resources.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    BmpImageData data;
    if (Resources::GetInstance().LoadBmpImage(&data, L"Test.bmp", 0, 0))
    {
        MessageBox(NULL, L"ASD", L"ASD", 0);
    }
    
    if (Game::GetInstance().Create(hInstance, nCmdShow))
    {
        Game::GetInstance().Run();
    }

    Game::GetInstance().Release();    
}