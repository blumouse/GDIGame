#pragma once

#include "INC_Windows.h"
#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

class Panel;
class PanelBitmap;

class PanelObject : public GameObjectBase, public IDrawable, public Transform
{
private:
    Panel* pPanel = nullptr;
    PanelBitmap* pPanelBitmap = nullptr;

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


    // Transform

    //bool IsIntersectPoint(int x, int y) override;
};