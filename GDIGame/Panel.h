#pragma once

#include "Component.h"
#include "IClickable.h"

class Panel : public Component, IClickable
{
    friend class GameManager;

private:
    bool isMine;
    bool isOpen;
    bool isMarked;

    Panel* pPanel_NW;
    Panel* pPanel_N;
    Panel* pPanel_NE;

    Panel* pPanel_W;
    Panel* pPanel_E;

    Panel* pPanel_SW;
    Panel* pPanel_S;
    Panel* pPanel_SE;

    int surroundingMine;

public:
    Panel() = delete;
    Panel(GameObjectBase* gameObject);

    ~Panel() override;

    void InitPanel();


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


private:
    void OpenPanel();
    void OpenLinkedPanel();

    void SetMarkedPanel();

    void ForceOpenLinkedPanel();
};