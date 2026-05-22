#pragma once
#include "Component.h"

class Panel;

class GameManager : public Component {
private:
    static GameManager* instance;

private:
    int row;
    int col;
    Panel* pPanels;        // row * col 크기의 동적 배열

    int mineAmount;
    int openedPanel;

    bool isBoom;

private:
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    static GameManager* GetInstance();
    static void DestroyInstance();

public:
    void InitGame(int row, int col, int mineAmount);

    void OnLClick(int mouseX, int mouseY);
    void OnRClick(int mouseX, int mouseY);

    void OnBoom(Panel* pBoomPanel);
    void OnPanelOpened();

    void GameOver();
    void FinalizeGame();

private:
    int CoordToPanelIndex(int mouseX, int mouseY) const;

    void InitPanels();
    void InitRandomMines();
    void InitPanelProps();

private:
    bool IsValidIndex(int index) const;
    bool IsValidCoord(int r, int c) const;

    int CoordToIndex(int r, int c) const;
    Panel* GetPanel(int r, int c) const;
};