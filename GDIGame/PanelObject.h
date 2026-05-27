#pragma once

#include "INC_Windows.h"
#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"
#include "RenderHelp.h"

namespace renderHelp
{
    class BitmapInfo;
}

class Panel;

// TODO: 이거 나중에 분리
class PanelBitmap : public Component
{
public:
    PanelBitmap() = delete;
    PanelBitmap(GameObjectBase* gameObject) : Component(gameObject) {}

    ~PanelBitmap() override;
};

class PanelObject : public GameObjectBase, IDrawable, Transform 
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    Panel* pPanel = nullptr;
    PanelBitmap* pPanelBitmap = nullptr;

public:
    PanelObject();
    PanelObject(const PanelObject&) = delete;

    ~PanelObject() override;

    Panel* GetPanel() const { return pPanel; }
    PanelBitmap* GetPanelBitmap() const { return pPanelBitmap; }


    // GameObjectBase (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // IDrawable
    void Draw(HDC hdc) override;


    // Transform
    bool IsIntersectPoint(int x, int y) override;
};