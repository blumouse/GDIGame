#pragma once
#include "NzWndBase.h"
#include "Utillity.h"

class GameTimer;
class GameObjectBase;
class IDrawable;
class Transform;

namespace renderHelp
{
    class BitmapInfo;
}

class Game : public NzWndBase
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    static Game* instance;

    GameObjectBase** ppGameObjects = nullptr;
    int gameObjectIndex;
    IDrawable** ppDrawables = nullptr;
    Transform** ppTransforms = nullptr;

    GameTimer* pGameTimer = nullptr;
    float fDeltaTime = 0.0f;
    float fFrameCount = 0.0f;

    BitmapInfo** ppBitmapResources = nullptr;


    HDC m_hFrontDC = nullptr;
    HDC m_hBackDC = nullptr;
    HBITMAP m_hBackBitmap = nullptr;
    HBITMAP m_hDefaultBitmap = nullptr;


public:
    Game() = default;
    ~Game() override = default;

    static Game* GetInstance();
    static void DestroyInstance();

    bool Initialize();
    void Run();
    void Finalize();


    void RegisterObject(GameObjectBase* gameObject);
    void RegisterDrawable(IDrawable* drawable);
    void RegisterTransform(Transform* transform);

    bool TryGetObjectWithPos(int mouseX, int mouseY, GameObjectBase*& goBase);


private:
    void _Update();     // Lifecycle 순서대로 호출
    void _Render();     // Drawable 찾아다 그리기 호출 후 제출

    // Lifecycles
    void Awake();
    void Start();
    void Update();
    void FixedUpdate();

    // 원래는 이벤트가 맞겠지만..
    // 임시로 클릭 매니저 갖다가 직접 호출 Handle~
    void OnMouseMove(int x, int y);
    void OnLButtonDown(int x, int y);
    void OnLButtonUp(int x, int y);
    void OnRButtonDown(int x, int y);
    void OnRButtonUp(int x, int y);


    void OnResize(int width, int height) override;
    void OnClose() override;


    void LoadResources();


private:
    struct MOUSE_POS
    {
        int x = 0;
        int y = 0;

        bool operator!=(const MOUSE_POS& other) const
        {
            return (x != other.x || y != other.y);
        }
    };

    BitmapInfo* m_pPlayerBitmapInfo = nullptr;
    BitmapInfo* m_pEnemyBitmapInfo = nullptr;
};