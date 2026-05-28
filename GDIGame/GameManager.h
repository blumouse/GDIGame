#pragma once

#include "Component.h"

class Panel;

class GameManager : public Component {
private:
    static GameManager* instance;

    const int ROW = 50;
    const int COL = 50;

    const int MINE_AMOUNT = 100;

    // row * col 크기의 동적 배열
    Panel** ppPanels;

    int openedPanel;

    bool isBoom;


public:
    GameManager() = delete;
    GameManager(GameObjectBase* gameObject) : Component(gameObject) { }

    ~GameManager() override = default;

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // Own Logic

    // Singleton
    static GameManager* GetInstance();
    //static void DestroyInstance();


    void InitGame(int row, int col, int mineAmount);

    void OnBoom(Panel* pBoomPanel);
    void OnPanelOpened();

    void GameOver();
    void FinalizeGame();


private:
    void InitPanels(int row, int col);
    void InitRandomMines(int mineAmount);
    void InitPanelProps();
};