#pragma once

#include "Component.h"
#include "IClickable.h"

class PanelBitmap;

class Panel : public Component, public IClickable
{
    friend class PanelBitmap;
    friend class GameManager;

private:
    // 이것들 조합해서 상태 따라 Draw하면 또 되겠군
    bool isMine = false;
    bool isOpen = false;
    bool isMarked = false;

    int surroundingMine = 0;


    Panel* pPanel_NW = nullptr;
    Panel* pPanel_N = nullptr;
    Panel* pPanel_NE = nullptr;

    Panel* pPanel_W = nullptr;
    Panel* pPanel_E = nullptr;

    Panel* pPanel_SW = nullptr;
    Panel* pPanel_S = nullptr;
    Panel* pPanel_SE = nullptr;

    PanelBitmap* panelBitmap = nullptr;

public:
    Panel() = delete;
    Panel(GameObjectBase* gameObject) : Component(gameObject) {}

    ~Panel() override = default;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // Clickable    
    void OnMouseEnter() override;
    void OnMouseExit() override;

    void OnLDown() override;
    void OnLComplete() override;
    void OnLCancel() override;

    void OnRDown() override;
    void OnRComplete() override;
    void OnRCancel() override;


    // Own Logic
    void InitPanel();


private:
    void OpenPanel();
    void OpenLinkedPanel();

    void SetMarkedPanel();

    void ForceOpenLinkedPanel();
    void ForceOpenPanel();
};