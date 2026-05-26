#include "Game.h"
#include "GameTimer.h"
#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

#include <iostream>
#include <assert.h>
#include "RenderHelp.h"

#include "GameManagerObject.h"
#include "ClickableManagerObject.h"
#include "PanelObject.h"

#include "ClickableManager.h"

using namespace learning;

// TODO: 
// 이니셜라이즈 / 파이널라이즈 / 로드 리소스 만들기
// 게임 자체도 전역으로 있어야할게 있는거같은데 Game::으로 호출되는것들
// pch 하나 묶어서 놔둘까?

// 어디부터 만드는게 나을까..?
// 프레임워크부터 만드는게 낫겠지? 대강 호출순서로 위에부터


constexpr int MAX_GAME_OBJECT_COUNT = 1000;

Game* Game::GetInstance() 
{
    if (instance == nullptr)
    {
        instance = new Game;
    }

    return instance;
}

void Game::DestroyInstance() 
{
    delete instance;
}


bool Game::Initialize()
{
    pGameTimer = new GameTimer();
    pGameTimer->Reset();

    const wchar_t* className = L"MiniGame";
    const wchar_t* windowName = L"지뢰찾기";

    if (false == __super::Create(className, windowName, 1024, 720))
    {
        return false;
    }


    RECT rcClient = {};
    GetClientRect(m_hWnd, &rcClient);
    m_width = rcClient.right - rcClient.left;
    m_height = rcClient.bottom - rcClient.top;

    m_hFrontDC = GetDC(m_hWnd);
    m_hBackDC = CreateCompatibleDC(m_hFrontDC);
    m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

    m_hDefaultBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);


    ppGameObjects = new GameObjectBase * [MAX_GAME_OBJECT_COUNT];
    ppDrawables = new IDrawable * [MAX_GAME_OBJECT_COUNT];
    ppTransforms = new Transform * [MAX_GAME_OBJECT_COUNT];

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        ppGameObjects[i] = nullptr;
        ppDrawables[i] = nullptr;
        ppTransforms[i] = nullptr;
    }

    gameObjectIndex = 0;    // 인덱스가 1000을 넘으면..? 그냥 생성용으로만 써야하나


    // 생성!!
    ClickableManagerObject* cmo = new ClickableManagerObject();
    cmo->Awake();
    ppGameObjects[gameObjectIndex++] = cmo;

    GameManagerObject* gmo = new GameManagerObject();
    gmo->Awake();   // 여기서 말고 생성자에서 호출해주는게? 응 안돼
    ppGameObjects[gameObjectIndex++] = gmo;

    // 패널은 게임매니저에서 생성..!
    // Awake 내에서 해야겟군


    // 다하고서 Start
    Start();



#pragma region resource
    m_pPlayerBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/redbird.png");
    m_pEnemyBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/graybird.png");

#pragma endregion



    return true;
}



void Game::Run()
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_MOUSEMOVE)
            {
                Game::OnMouseMove(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_LBUTTONDOWN)
            {
                Game::OnLButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_RBUTTONDOWN)
            {
                Game::OnRButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_LBUTTONUP)
            {
                Game::OnLButtonUp(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_RBUTTONUP)
            {
                Game::OnRButtonUp(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            _Update();
            _Render();
        }
    }
}


void Game::Finalize()
{
    delete pGameTimer;
    pGameTimer = nullptr;

    if (ppTransforms)
    {
        // 컴포넌트 들어가서 그것들도 없애주기
        delete ppTransforms;
    }

    if (ppDrawables)
    {
        delete ppDrawables;
    }

    if (ppGameObjects)
    {
        for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
        {
            if (ppGameObjects[i])
            {
                delete ppGameObjects[i];
                ppGameObjects[i] = nullptr;
            }
        }
        delete ppGameObjects;
    }

    __super::Destroy();
}


void Game::_Update()
{
    pGameTimer->Tick();

    Update();

    fDeltaTime = pGameTimer->DeltaTimeMS();
    fFrameCount += fDeltaTime;

    while (fFrameCount >= 200.0f)
    {
        FixedUpdate();
        fFrameCount -= 200.0f;
    }
}


void Game::_Render()
{
    //Clear the back buffer
    ::PatBlt(m_hBackDC, 0, 0, m_width, m_height, WHITENESS);

    //메모리 DC에 그리기
    //for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    //{
    //    if (ppGameObjects[i])
    //    {
    //        ppGameObjects[i]->Render(m_hBackDC);
    //    }
    //}

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (ppDrawables[i])
        {
            ppDrawables[i]->Draw(m_hBackDC);
        }
    }

    //메모리 DC에 그려진 결과를 실제 DC(m_hFrontDC)로 복사
    BitBlt(m_hFrontDC, 0, 0, m_width, m_height, m_hBackDC, 0, 0, SRCCOPY);
}


void Game::Awake() 
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (ppGameObjects[i])
        {
            ppGameObjects[i]->Awake();
        }
        else
            break;
    }
}


void Game::Start()
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (ppGameObjects[i])
        {
            ppGameObjects[i]->Start();
        }
        else
            break;
    }
}


void Game::Update()
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (ppGameObjects[i])
        {
            ppGameObjects[i]->Update(fDeltaTime);
        }
        else
            break;
    }
}


void Game::FixedUpdate()
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (ppGameObjects[i])
        {
            ppGameObjects[i]->FixedUpdate();
        }
        else
            break;
    }
}


void Game::OnMouseMove(int x, int y)
{
    ClickableManager::GetInstance()->HandleMouseMove(x, y);
}

void Game::OnLButtonDown(int x, int y)
{
    ClickableManager::GetInstance()->HandleLDown(x, y);
}

void Game::OnRButtonDown(int x, int y)
{
    ClickableManager::GetInstance()->HandleRDown(x, y);
}

void Game::OnLButtonUp(int x, int y)
{
    ClickableManager::GetInstance()->HandleLUp(x, y);
}

void Game::OnRButtonUp(int x, int y)
{
    ClickableManager::GetInstance()->HandleRUp(x, y);
}


void Game::OnResize(int width, int height)
{
    std::cout << __FUNCTION__ << std::endl;

    learning::SetScreenSize(width, height);

    __super::OnResize(width, height);

    m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

    HANDLE hPrevBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);

    DeleteObject(hPrevBitmap);
}


void Game::OnClose()
{
    std::cout << __FUNCTION__ << std::endl;

    SelectObject(m_hBackDC, m_hDefaultBitmap);

    DeleteObject(m_hBackBitmap);
    DeleteDC(m_hBackDC);

    ReleaseDC(m_hWnd, m_hFrontDC);
}


void Game::LoadResources() 
{

}


void Game::RegisterObject(GameObjectBase* gameObject)
{
    ppGameObjects[gameObjectIndex++] = gameObject;
}

void Game::RegisterDrawable(IDrawable* drawable)
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
    {
        if (ppDrawables[i] == nullptr)
        {
            ppDrawables[i] = drawable;
            break;
        }
    }
}

void Game::RegisterTransform(Transform* transform)
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
    {
        if (ppTransforms[i] == nullptr)
        {
            ppTransforms[i] = transform;
            break;
        }
    }
}


bool Game::TryGetObjectWithPos(int mouseX, int mouseY, GameObjectBase*& goBase)
{
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; i++)
    {
        if (ppTransforms[i])
        {
            ppTransforms[i]->pos
        }
        else
            return false;
    }
}