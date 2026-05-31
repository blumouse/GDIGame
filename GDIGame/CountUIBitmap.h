#pragma once

#include "Component.h"
#include "RenderHelp.h"

namespace renderHelp
{
    class BitmapInfo;
}

enum CountState
{
    Count_0 = 11,
    Count_1 = 10,
    Count_2 = 9,
    Count_3 = 8,
    Count_4 = 7,
    Count_5 = 6,
    Count_6 = 5,
    Count_7 = 4,
    Count_8 = 3,
    Count_9 = 2,
    Count_Blank = 1,
    Count_Dash = 0,
};


class CountUIBitmap : public Component
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    BitmapInfo* pCountUIBitmapInfo = nullptr;

    CountState count = Count_Dash;

public:
    CountUIBitmap() = delete;
    CountUIBitmap(GameObjectBase* gameObject) : Component(gameObject) {}

    ~CountUIBitmap() override = default;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    void InitCountUIInfo(int num);
    void SetCountUIInfo(int num);


    BitmapInfo* GetCountUIBitmapInfo() const { return pCountUIBitmapInfo; }
    int GetCurNumber() const { return (int)count; }

    static const int COUNTUI_BITMAP_SLICE_WIDTH = 16;
    static const int COUNTUI_BITMAP_SLICE_HEIGHT = 28;  // 아 리사이징 잘못했어 ..여기까지 해야겟다


private:
    void SetCount(CountState countState);

    void SetCountUIBitmapInfo();

};

