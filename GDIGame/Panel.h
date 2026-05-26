#pragma once

#include "Component.h"
#include "IClickable.h"

class Panel : public IClickable
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
    Panel();
    ~Panel();

    void InitPanel();

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