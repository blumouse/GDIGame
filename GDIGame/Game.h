#pragma once
#include "NzWndBase.h"
#include "Utillity.h"
#include "RenderHelp.h"

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
    int gameObjectsIndex = 0;
    IDrawable** ppDrawables = nullptr;
    Transform** ppTransforms = nullptr;

    GameTimer* pGameTimer = nullptr;
    float fDeltaTime = 0.0f;
    float fFrameCount = 0.0f;

    // 이건 걍 좀 강력하게 쓸까
    BitmapInfo** ppBitmapResources = nullptr;


    HDC m_hFrontDC = nullptr;
    HDC m_hBackDC = nullptr;
    HBITMAP m_hBackBitmap = nullptr;
    HBITMAP m_hDefaultBitmap = nullptr;


public:
    Game() = default;
    ~Game() override = default;

    static Game* GetInstance();
    //static void DestroyInstance();    필요 없는듯? 생성한 쪽에서 지워야지

    bool Initialize();
    void Run();
    void Finalize();


    void RegisterObject(GameObjectBase* gameObject);
    void RegisterDrawable(IDrawable* drawable);
    void RegisterTransform(Transform* transform);

    void DestroyObject(GameObjectBase* gameObject);

    bool TryGetObjectWithPos(int mouseX, int mouseY, GameObjectBase*& gameObject);


private:
    void _Update();     // Lifecycle 순서대로 호출
    void _Render();     // Drawable 찾아다 그리기 호출 후 제출

    // Lifecycles
    void Awake();       // 미사용, Register시 호출
    void Start();       // 초기화 시 Awake 후 호출, 초기화 끝났다면 Register 시 함께 호출
    void Update();
    void FixedUpdate();
    void OnDestroy();   // 미사용, Destroy 시 호출

    bool isStarted = false;

    // 원래는 이벤트가 맞겠지만..
    // 임시로 클릭 매니저 갖다가 직접 호출 Handle~
    void OnMouseMove(int x, int y);
    void OnLButtonDown(int x, int y);
    void OnLButtonUp(int x, int y);
    void OnRButtonDown(int x, int y);
    void OnRButtonUp(int x, int y);


    void OnResize(int width, int height) override;
    void OnClose() override;


    bool LoadResources();


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