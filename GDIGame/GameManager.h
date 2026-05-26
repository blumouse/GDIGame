#pragma once

#include "Component.h"

class Panel;

class GameManager : public Component {
private:
    static GameManager* instance;

    int row;
    int col;
    Panel* pPanels;        // row * col 크기의 동적 배열

    int mineAmount;
    int openedPanel;

    bool isBoom;


public:
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    static GameManager* GetInstance();
    static void DestroyInstance();


    void InitGame(int row, int col, int mineAmount);

    void OnBoom(Panel* pBoomPanel);
    void OnPanelOpened();

    void GameOver();
    void FinalizeGame();


    void InitPanels();
    void InitRandomMines();
    void InitPanelProps();
};