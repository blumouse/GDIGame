#pragma once
#include "NzWndBase.h"
#include "Utillity.h"

class GameTimer;
class GameObjectBase;
class IDrawable;

namespace renderHelp
{
    class BitmapInfo;
}

class Game : public NzWndBase
{
    using BitmapInfo = renderHelp::BitmapInfo;

public:
    Game() = default;
    ~Game() override = default;

    bool Initialize();
    void Run();
    void Finalize();

private:
    void _Update();
    void _Render();


    void Awake();
    void Start();
    void Update();
    void FixedUpdate();

    void OnMouseMove(int x, int y);
    void OnLButtonDown(int x, int y);
    void OnRButtonDown(int x, int y);


    void OnResize(int width, int height) override;
    void OnClose() override;

private:
    GameObjectBase** ppGameObjects = nullptr;
    IDrawable** ppDrawableObjects = nullptr;

    GameTimer* pGameTimer = nullptr;
    float fDeltaTime = 0.0f;
    float fFrameCount = 0.0f;

    BitmapInfo** ppBitmapResources = nullptr;


    HDC m_hFrontDC = nullptr;
    HDC m_hBackDC = nullptr;
    HBITMAP m_hBackBitmap = nullptr;
    HBITMAP m_hDefaultBitmap = nullptr;


    void LoadResources();

    struct MOUSE_POS
    {
        int x = 0;
        int y = 0;

        bool operator!=(const MOUSE_POS& other) const
        {
            return (x != other.x || y != other.y);
        }
    };

    MOUSE_POS m_MousePos = { 0, 0 };
    MOUSE_POS m_MousePosPrev = { 0, 0 };

    BitmapInfo* m_pPlayerBitmapInfo = nullptr;
    BitmapInfo* m_pEnemyBitmapInfo = nullptr;
};