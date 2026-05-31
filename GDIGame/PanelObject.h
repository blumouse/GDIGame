#pragma once

#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

namespace renderHelp
{
    class BitmapInfo;
}

class Panel;
class PanelBitmap;

class PanelObject : public GameObjectBase, public IDrawable, public Transform
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    Panel* pPanel = nullptr;
    PanelBitmap* pPanelBitmap = nullptr;

    int layer = 0;

public:
    PanelObject();
    PanelObject(const PanelObject&) = delete;

    ~PanelObject() override = default;

    Panel* GetPanel() const { return pPanel; }
    PanelBitmap* GetPanelBitmap() const { return pPanelBitmap; }


    // GameObjectBase (Lifecycles)
    //void Awake() override;
    //void Start() override;
    //void Update(float deltaTime) override;
    //void FixedUpdate() override;

    //void OnDestroy() override;


    // IDrawable
    void Draw(HDC hdc) override;
    int GetLayer() override;
    void SetLayer(int layer) override;


    // Transform

    //bool IsIntersectPoint(int x, int y) override;
};