#include "Game.h"

#include "GamePlayer.h"
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
        srand((unsigned int)time(NULL));
        for (int i = 0; i < 6; i++)
        {
            game.RegisterObject(new GamePlayer(rand() % 600, rand() % 480));
        }        

        //game.RegisterObject(new GameManager());

        game.Run();
    }

    game.Release();
}