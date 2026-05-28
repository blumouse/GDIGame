#pragma once

#include "Component.h"
#include "Transform.h"

class Panel;

class GameManager : public Component {
private:
    static GameManager* instance;

    const int ROW = 20;
    const int COL = 20;

    const int MINE_AMOUNT = 120;

    const Vector2 panelScale = Vector2(20.0f, 20.0f);

    // row * col 크기의 동적 배열
    Panel** ppPanels = nullptr;

    int openedPanel = 0;

    bool isBoom = false;


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

    void GameOver(bool isSueccess);
    void FinalizeGame();


private:
    void InitPanels(int row, int col);
    void InitRandomMines(int row, int col, int mineAmount);
    void InitPanelProps(int row, int col);
};