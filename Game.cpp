#pragma comment(lib, "winmm.lib")

#include "Game.h"

#include "InputComponent.h"
#include "ObjectComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"

#include "GameObject.h"
#include "Resources.h"

bool Game::Create(HINSTANCE hInstance, int nCmdShow)
{
    mhInstance = hInstance;
    RegisterWindowClass();
    
    if (CreateWindowInstance(nCmdShow))
    {        
        CreateComponents();
        timeBeginPeriod(1);
        
        #pragma region 테스트 코드
        Position2D mapPivot = { 0, 0 };
        Position2D pivot = { 71, 90 };
        Resources::GetInstance().LoadSprite(L"Map", mapPivot);
        Resources::GetInstance().LoadSprite(L"Stand_L", pivot);
        Resources::GetInstance().LoadSprite(L"Stand_R", pivot);

        Resources::GetInstance().LoadSprite(L"Move_L", pivot);
        Resources::GetInstance().LoadSprite(L"Move_R", pivot);

        Resources::GetInstance().LoadSprite(L"Attack1_L", pivot);
        Resources::GetInstance().LoadSprite(L"Attack1_R", pivot);        
        #pragma endregion
        return true;
    }

    return false;
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
    timeEndPeriod(1);
}

void Game::RegisterObject(GameObject* object)
{
    //일단 오브젝트 생성은 됬고..
    //등록을 해야함    
    mGameObjects.push_back(object);
}

BaseComponent* Game::GetComponent(std::wstring_view componentName)
{
    for (auto component : mComponents)
    {
        if (component->GetName() == componentName)
        {
            return component;
        }
    }

    return nullptr;
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
    
    //WCHAR str2[32];
    //wsprintf(str2, L"spendTime : %d\n", spendTime);       //21ms 소모되면 47프레임이 나오네...
    //OutputDebugString(str2);
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
    : mhInstance(nullptr), mhWnd(nullptr)
{
}

Game::~Game()
{

}