#include "MyFirstWndGame.h"
#include "GameTimer.h"
#include "Collider.h"
#include "GameObject.h"
#include <iostream>
#include <assert.h>
#include "NzWndBase.h"
#include "RenderHelp.h"

using namespace learning;

constexpr int MAX_GAME_OBJECT_COUNT = 1000;

bool MyFirstWndGame::Initialize()
{
    m_pGameTimer = new GameTimer();
    m_pGameTimer->Reset();

    const wchar_t* className = L"MyFirstWndGame";
    const wchar_t* windowName = L"새가날아든다";

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

    m_GameObjectPtrTable = new GameObjectBase * [MAX_GAME_OBJECT_COUNT];

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        m_GameObjectPtrTable[i] = nullptr;
    }

#pragma region resource
    m_pPlayerBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/redbird.png");
    m_pEnemyBitmapInfo = renderHelp::CreateBitmapInfo(L"./Resource/graybird.png");

#pragma endregion

    // [CHECK]. 첫 번째 게임 오브젝트는 플레이어 캐릭터로 고정!
    CreatePlayer();

    return true;

}

void MyFirstWndGame::Run()
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
                MyFirstWndGame::OnLButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_RBUTTONDOWN)
            {
                MyFirstWndGame::OnRButtonDown(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else if (msg.message == WM_MOUSEMOVE)
            {
                MyFirstWndGame::OnMouseMove(LOWORD(msg.lParam), HIWORD(msg.lParam));
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Update();
            Render();
        }
    }
}

void MyFirstWndGame::Finalize()
{
    delete m_pGameTimer;
    m_pGameTimer = nullptr;

    if (m_GameObjectPtrTable)
    {
        for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
        {
            if (m_GameObjectPtrTable[i])
            {
                delete m_GameObjectPtrTable[i];
                m_GameObjectPtrTable[i] = nullptr;
            }
        }
        delete m_GameObjectPtrTable;
    }

    __super::Destroy();
}

void MyFirstWndGame::FixedUpdate()
{
    if (m_EnemySpawnPos.x != 0 && m_EnemySpawnPos.y != 0)
    {
        CreateEnemy();
    }

    // 이거 추가
    // 이제 그냥 다 검사하게 수정
    GameObject* go_1;
    GameObject* go_2;

    // 강력하게 초기화해버리자
    int i = -1;
    while (++i < MAX_GAME_OBJECT_COUNT) {
        go_1 = GetEnemy(i);
        if (nullptr == go_1)
            break;

        go_1->SetColor();
        go_1->isIntersect = false;
        for (int j = 0; j < go_1->IntersectColliders_index; j++)
            go_1->intersectColliders[j] = nullptr;
        go_1->IntersectColliders_index = 0;
    }

    i = -1;
    while (++i < MAX_GAME_OBJECT_COUNT)
    {
        go_1 = GetEnemy(i);     // 플레이어도 받아올수 있다..
        if (nullptr == go_1)
            break;

        for (int j = i + 1; j < MAX_GAME_OBJECT_COUNT; j++)
        {
            go_2 = GetEnemy(j);
            if (nullptr == go_2)
                break;

            if (learning::Intersect(*(go_1->m_pColliderCircle), *(go_2->m_pColliderCircle)))
            {
                // 컬러를 파란색으로 설정!
                go_1->SetColor(0, 0, 255);
                go_2->SetColor(0, 0, 255);

                // 플래그도 추가
                go_1->isIntersect = true;
                go_2->isIntersect = true;

                // 콜리전 정보도 추가
                go_1->intersectColliders[go_1->IntersectColliders_index++] = go_2;
                go_2->intersectColliders[go_2->IntersectColliders_index++] = go_1;
            }
        }
    }
}

void MyFirstWndGame::LogicUpdate()
{
    UpdatePlayerInfo();

    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (m_GameObjectPtrTable[i])
        {
            if (i != 0)
                UpdateEnemyInfo(i);

            m_GameObjectPtrTable[i]->Update(m_fDeltaTime);
        }
    }
}

void MyFirstWndGame::CreatePlayer()
{
    assert(m_GameObjectPtrTable[0] == nullptr && "Player object already exists!");

    GameObject* pNewObject = new GameObject(ObjectType::PLAYER);

    pNewObject->SetName("Player");
    pNewObject->SetPosition(0.0f, 0.0f); // 일단, 임의로 설정 
    pNewObject->SetSpeed(1.0f); // 일단, 임의로 설정   
    pNewObject->SetColor();    // 이거 추가

    pNewObject->SetColliderCircle(50.0f); // 일단, 임의로 설정. 오브젝트 설정할 거 다 하고 나서 하자.

    pNewObject->SetBitmapInfo(m_pPlayerBitmapInfo);

    pNewObject->SetWidth(100);
    pNewObject->SetHeight(100);

    pNewObject->intersectColliders = new GameObject* [MAX_GAME_OBJECT_COUNT];

    m_GameObjectPtrTable[0] = pNewObject;
}

void MyFirstWndGame::CreateEnemy()
{
    GameObject* pNewObject = new GameObject(ObjectType::ENEMY);

    pNewObject->SetName("Enemy");

    float x = m_EnemySpawnPos.x;
    float y = m_EnemySpawnPos.y;

    m_EnemySpawnPos = { 0, 0 };

    pNewObject->SetPosition(x, y);
    pNewObject->SetSpeed(0.5f); // 너무 빨라

    pNewObject->SetColliderCircle(50.0f); // 일단, 임의로 설정. 오브젝트 설정할 거 다 하고 나서 하자.
    pNewObject->SetColor();

    pNewObject->SetBitmapInfo(m_pEnemyBitmapInfo);

    pNewObject->SetWidth(100);
    pNewObject->SetHeight(100);

    pNewObject->intersectColliders = new GameObject* [MAX_GAME_OBJECT_COUNT];

    int i = 0;
    while (++i < MAX_GAME_OBJECT_COUNT) //0번째는 언제나 플레이어!
    {
        // 이거 추가
        if (nullptr != m_GameObjectPtrTable[i])
        {
            if (learning::Intersect(*(pNewObject->m_pColliderCircle), *(GetEnemy(i)->m_pColliderCircle)))
            {
                m_EnemySpawnPos = { 0, 0 };
                delete pNewObject;
                return;
            }
        }
        else if (nullptr == m_GameObjectPtrTable[i])
        {
            m_GameObjectPtrTable[i] = pNewObject;
            break;
        }
    }

    if (i == MAX_GAME_OBJECT_COUNT)
    {
        // 게임 오브젝트 테이블이 가득 찼습니다.
        delete pNewObject;
        pNewObject = nullptr;
    }
}

void MyFirstWndGame::UpdatePlayerInfo()
{
    static GameObject* pPlayer = GetPlayer();

    assert(pPlayer != nullptr);

    Vector2f mousePos(m_PlayerTargetPos.x, m_PlayerTargetPos.y);
    Vector2f playerPos = pPlayer->GetPosition();

    Vector2f playerDir = mousePos - playerPos;
    float distance = playerDir.Length(); // 거리 계산

    // 진행방향에 적이 있으면 못가게 하고싶다!
    playerDir.Normalize(); // 정규화
    pPlayer->SetDirection(playerDir); // 플레이어 방향 설정

    if (distance > 50.f && !pPlayer->isIntersect)
    {
        // 예의상 넣어줘야한다
    }
    else if (distance > 50.f && pPlayer->isIntersect) //임의로 설정한 거리
    {
        GameObject* go = nullptr;
        bool isMoveable = true;

        Vector2f enemyPos;
        Vector2f enemyDir;

        for (int i = 0; i < pPlayer->IntersectColliders_index; i++)
        {
            go = pPlayer->intersectColliders[i];
            if (go == nullptr)
                break;

            // 벡터로 어쩌구해서 반대방향일때만 이동가능~
            enemyPos = go->GetPosition();
            enemyDir = enemyPos - playerPos;
            enemyDir.Normalize();

            // 대강 90도보다 커야한다
            if (playerDir.Dot(enemyDir) > 0.25f)    // 인간미
                isMoveable = false;
        }

        if (!isMoveable)
        {
            pPlayer->SetDirection(Vector2f(0, 0));
            m_PlayerTargetPos.x = playerPos.x;
            m_PlayerTargetPos.y = playerPos.y;
        }
    }
    else
    {
        pPlayer->SetDirection(Vector2f(0, 0)); // 플레이어 정지
    }
}

void MyFirstWndGame::UpdateEnemyInfo(int i) {
    GameObject* pEnemy = GetEnemy(i);
    static GameObject* pPlayer = GetPlayer();

    assert(pEnemy != nullptr);

    Vector2f playerPos = pPlayer->GetPosition();
    Vector2f enemyPos = pEnemy->GetPosition();

    Vector2f enemyDir = playerPos - enemyPos;

    enemyDir.Normalize();
    pEnemy->SetDirection(enemyDir);

    // 플래그를 이용하자
    if (pEnemy->isIntersect)
    {
        GameObject* go = nullptr;
        bool isMoveable = true;

        Vector2f otherPos;
        Vector2f otherDir;

        for (int i = 0; i < pEnemy->IntersectColliders_index; i++)
        {
            go = pEnemy->intersectColliders[i];
            if (go == nullptr)
                break;

            otherPos = go->GetPosition();
            otherDir = otherPos - enemyPos;
            otherDir.Normalize();

            if (enemyDir.Dot(otherDir) > 0.25f)
                isMoveable = false;
        }

        if (!isMoveable)
        {
            pEnemy->SetDirection(Vector2f(0, 0));
        }
    }
}

void MyFirstWndGame::Update()
{
    m_pGameTimer->Tick();

    LogicUpdate();

    m_fDeltaTime = m_pGameTimer->DeltaTimeMS();
    m_fFrameCount += m_fDeltaTime;

    while (m_fFrameCount >= 20.0f)      // 너무 가끔 호출해서 너무 뚫고 들어가자나
    {
        FixedUpdate();
        m_fFrameCount -= 20.0f;
    }
}

void MyFirstWndGame::Render()
{
    //Clear the back buffer
    ::PatBlt(m_hBackDC, 0, 0, m_width, m_height, WHITENESS);

    //메모리 DC에 그리기
    for (int i = 0; i < MAX_GAME_OBJECT_COUNT; ++i)
    {
        if (m_GameObjectPtrTable[i])
        {
            m_GameObjectPtrTable[i]->Render(m_hBackDC);
        }
    }

    //메모리 DC에 그려진 결과를 실제 DC(m_hFrontDC)로 복사
    BitBlt(m_hFrontDC, 0, 0, m_width, m_height, m_hBackDC, 0, 0, SRCCOPY);
}

void MyFirstWndGame::OnResize(int width, int height)
{
    std::cout << __FUNCTION__ << std::endl;

    learning::SetScreenSize(width, height);

    __super::OnResize(width, height);

    m_hBackBitmap = CreateCompatibleBitmap(m_hFrontDC, m_width, m_height);

    HANDLE hPrevBitmap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitmap);

    DeleteObject(hPrevBitmap);
}

void MyFirstWndGame::OnClose()
{
    std::cout << __FUNCTION__ << std::endl;

    SelectObject(m_hBackDC, m_hDefaultBitmap);

    DeleteObject(m_hBackBitmap);
    DeleteDC(m_hBackDC);

    ReleaseDC(m_hWnd, m_hFrontDC);
}

void MyFirstWndGame::OnMouseMove(int x, int y)
{
    /*   std::cout << __FUNCTION__ << std::endl;
       std::cout << "x: " << x << ", y: " << y << std::endl;*/
    m_MousePosPrev = m_MousePos;
    m_MousePos = { x, y };
}

void MyFirstWndGame::OnLButtonDown(int x, int y)
{
    /*  std::cout << __FUNCTION__ << std::endl;
 std::cout << "x: " << x << ", y: " << y << std::endl;*/

    m_PlayerTargetPos.x = x;
    m_PlayerTargetPos.y = y;

}

void MyFirstWndGame::OnRButtonDown(int x, int y)
{
    /*  std::cout << __FUNCTION__ << std::endl;
   std::cout << "x: " << x << ", y: " << y << std::endl;*/

    m_EnemySpawnPos.x = x;
    m_EnemySpawnPos.y = y;
}