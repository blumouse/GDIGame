#pragma once

#include "Component.h"
#include "RenderHelp.h"


namespace renderHelp
{
    class BitmapInfo;
}

enum ClickState
{
    Enter,
    Exit,
    LDown,
    LComplete,
    LCancel,
    RDown,
    RComplete,
    RCancel,
};

enum AnimState
{
    Idle,
    Highlighted,
    Down,
};

enum SpriteState 
{
    Covered = 0,
    Marked = 1,
    Opened_Mine = 3,
    Opened_Blank = 15,
    Opened_1 = 14,
    Opened_2 = 13,
    Opened_3 = 12,
    Opened_4 = 11,
    Opened_5 = 10,
    Opened_6 = 9,
    Opened_7 = 8,
    Opened_8 = 7,
};


class PanelBitmap : public Component
{
    using BitmapInfo = renderHelp::BitmapInfo;

private:
    bool isMine = false;
    bool isOpen = false;
    bool isMarked = false;
    int surroundingMine = 0;

    ClickState prevState = Exit;


    BitmapInfo* pPanelBitmapInfo = nullptr;
    AnimState anim = Idle;
    SpriteState sprite = Covered;

public:
    PanelBitmap() = delete;
    PanelBitmap(GameObjectBase* gameObject) : Component(gameObject) {}

    ~PanelBitmap() override = default;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    void InitPanelInfo(bool isMine, int surroundingMine);

    void SetClickState(ClickState clickState);
    void SetPanelInfo(bool isOpen, bool isMarked);


    BitmapInfo* GetPanelBitmapInfo() const { return pPanelBitmapInfo; }
    int GetAnimIndex() const { return (int)anim; }
    int GetSpriteIndex() const { return (int)sprite; }

    static const int PANEL_BITMAP_SLICE_WIDTH = 20;
    static const int PANEL_BITMAP_SLICE_HEIGHT = 20;
    
private:
    void SetAnim(AnimState animState);
    void SetSprite(SpriteState spriteState);

    void SetPanelBitmapInfo();

};