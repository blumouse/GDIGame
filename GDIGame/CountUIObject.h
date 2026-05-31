#pragma once

#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

namespace renderHelp
{
    class BitmapInfo;
}

class CountUI;
class CountUIBitmap;


class CountUIObject : public GameObjectBase, public IDrawable, public Transform
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    CountUI* pCountUI = nullptr;
    CountUIBitmap* pCountUIBitmap = nullptr;

    int layer = 0;

public:
    CountUIObject();
    CountUIObject(const CountUIObject&) = delete;

    ~CountUIObject() override = default;

    CountUI* GetCountUI() const { return pCountUI; }
    CountUIBitmap* GetCountUIBitmap() const { return pCountUIBitmap; }


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

