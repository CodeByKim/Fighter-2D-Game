#include "Game.h"

#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    Game& game = Game::GetInstance();

    if (game.Create(hInstance, nCmdShow))
    {                
        GameManager* gameManager = new GameManager();
        game.Run();
    }

    game.Release();
}