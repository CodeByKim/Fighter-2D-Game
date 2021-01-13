#include "Game.h"
#include "Resources.h"
#include "Sprite.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    //Sprite* sprite = Sprite::Create(L"Test.bmp");
    //sprite->SetPivot(71, 90);    
    
    if (Game::GetInstance().Create(hInstance, nCmdShow))
    {
        Game::GetInstance().Run();
    }

    Game::GetInstance().Release();    
}