#pragma once
#include "Component.h"

class Panel
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

public:
    void InitPanel();

    void OnLClickPanel();
    void OnRClickPanel();

private:
    void OpenPanel();
    void OpenLinkedPanel();

    void SetMarkedPanel();

    void ForceOpenLinkedPanel();

private:
    bool CanOpen() const;
    bool IsEmptyPanel() const;
};