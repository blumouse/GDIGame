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

// 어디부터 만드는게 나을까..?
// 프레임워크부터 만드는게 낫겠지? 대강 호출순서로 위에부터
// 0.01% 유니티

// 크게 프레임워크 구현 / 클릭ux 구현 / 게임로직 구현 으로 나누자
// 아 비트맵도 연결해야됨;

// TODO: 
// pch 하나 묶어서 놔둘까?
// Transform 함수 구현
// 패널에서 Drawable 구현해보기
// 
// 클릭매니저 구현하기 전까진 마우스함수 지워놓고 해야겠군;
// 로드 리소스 만들기

// 엄 어디까지 된거지 프레임워크..?
// gmo부분 테스트겸 만들어보면서 또 하니까 좀 헷갈
// 일단 내부로직 안채우고 흰화면부터 띄워보자


constexpr int MAX_GAME_OBJECT_COUNT = 10000;

Game* Game::GetInstance() 
{
    return instance;
}


bool Game::Initialize()
{
    // 싱글톤
    if (instance != nullptr && instance != this)
    {
        return false;
    }
    else /*if (instance == nullptr)*/
    {
        instance = this;
    }


    // 초초기화 0
    pGameTimer = new GameTimer();
    pGameTimer->Reset();

    const wchar_t* className = L"MiniGame";
    const wchar_t* windowName = L"지뢰찾기";

    if (false == __super::Create(className, windowName, 1024, 720))
    {
        return false;
    }


    // 초초기화 1
    RECT rcClient = {};
    GetClientRect(m_hWnd, &rcClient);
    m_width = rcClient.right - rcClient.left;
    m_height = rcClient.bottom - rcClient.top;

    m_hFrontDC = GetDC(m_hWnd);
    m_hBackDC = CreateCompatibleDC(m_hFrontDC);
    m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

    m_hDefaultBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);


    // 초초기화 2
    //if (!LoadResources())
    //{
    //    return false;
    //}


    // 게임 초기화
    ppGameObjects = new GameObjectBase* [MAX_GAME_OBJECT_COUNT];
    ppDrawables = new IDrawable* [MAX_GAME_OBJECT_COUNT];
    ppTransforms = new Transform* [MAX_GAME_OBJECT_COUNT];

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        ppGameObjects[i] = nullptr;
        ppDrawables[i] = nullptr;
        ppTransforms[i] = nullptr;
    }

    gameObjectsIndex = 0;


    // 생성!!
    // 유니티로 치면.. 하이라키에 올라가있는 오브젝트들
    ClickableManagerObject* cmo = new ClickableManagerObject();
    //RegisterObject(cmo);

    GameManagerObject* gmo = new GameManagerObject();
    //RegisterObject(gmo);

    // 패널은 게임매니저에서 생성(인스턴트)..!
    // Awake 내에서 일단 해야겟군


    // 다하고서 Start
    Start();
    isStarted = true;       // 이후에 생성되는 놈들은 따로 호출해줌


    // 이게 먼저 와야겠네 이렇게는 안할거지만
    //m_pPlayerBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/redbird.png");
    //m_pEnemyBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/graybird.png");

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
        delete ppTransforms;
        ppTransforms = nullptr;
    }

    if (ppDrawables)
    {
        delete ppDrawables;
        ppDrawables = nullptr;
    }

    if (ppGameObjects)
    {
        for (int i = 0; i < gameObjectsIndex; ++i)
        {
            if (ppGameObjects[i])
            {
                ppGameObjects[i]->OnDestroy();

                // 는 오브젝트 소멸자에서 알아서 해주구요~
                //Component** components = ppGameObjects[i]->GetComponents();

                //for (int j = 0; j < ppGameObjects[i]->GetComponentsSize(); j++)
                //{
                //    delete components[j];
                //}

                delete ppGameObjects[i];
                ppGameObjects[i] = nullptr;
            }
        }
        delete ppGameObjects;
        ppGameObjects = nullptr;
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


//void Game::Awake() 
//{
//    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
//    {
//        if (ppGameObjects[i])
//        {
//            ppGameObjects[i]->Awake();
//        }
//        else
//            break;
//    }
//}


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


//void Game::LoadResources() 
//{
//
//}


void Game::RegisterObject(GameObjectBase* gameObject)
{
    // 효율적인 검색을 위한..

    for (int i = 0; i < gameObjectsIndex; i++)
    {
        if (ppGameObjects[i] == nullptr)
        {
            ppGameObjects[i] = gameObject;
            gameObject->Awake();

            if (isStarted)
                gameObject->Start();

            return;
        }
    }


    if (gameObjectsIndex == MAX_GAME_OBJECT_COUNT)
        // 안돼
        return;

    ppGameObjects[gameObjectsIndex++] = gameObject;
    gameObject->Awake();

    if (isStarted)
        gameObject->Start();
}

void Game::RegisterDrawable(IDrawable* drawable)
{
    for (int i = 0; i < gameObjectsIndex; i++)
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
    for (int i = 0; i < gameObjectsIndex; i++)
    {
        if (ppTransforms[i] == nullptr)
        {
            ppTransforms[i] = transform;
            break;
        }
    }
}


void Game::DestroyObject(GameObjectBase* gameObject) 
{
    for (int i = 0; i < gameObjectsIndex; i++)
    {
        if (ppTransforms[i])
        {
            if (ppTransforms[i] == dynamic_cast<Transform*>(gameObject))      // ?? 이거 되나..?
                ppTransforms[i] = nullptr;              // 그냥 이쪽은 따로 탈퇴시키는게 낫나
        }

        if (ppDrawables[i])
        {
            if (ppDrawables[i] == dynamic_cast<IDrawable*>(gameObject))
                ppDrawables[i] = nullptr;
        }

        if (ppGameObjects[i])
        {
            if (ppGameObjects[i] == gameObject)
            {
                ppGameObjects[i] = nullptr;

                gameObject->OnDestroy();
                delete gameObject;

                return;
            }
        }
    }

    // 여기 왔으면.. 너 뭐임
    assert(gameObject == nullptr);
}


bool Game::TryGetObjectWithPos(int mouseX, int mouseY, GameObjectBase*& gameObject)
{
    for (int i = 0; i < gameObjectsIndex; i++)
    {
        if (ppTransforms[i])
        {
            if (ppTransforms[i]->IsIntersect(mouseX, mouseY))
            {
                // 어 그 주소 go 맞아.. 더 확실하게 보장시킬수 없나 transform에?
                gameObject = dynamic_cast<GameObjectBase*>(ppTransforms[i]);
                return true;
            }
        }
        else
            return false;
    }

    return false;
}