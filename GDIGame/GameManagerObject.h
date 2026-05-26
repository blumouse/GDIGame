#pragma once

#include "INC_Windows.h"
#include "MyGameObject.h"


// 컴포넌트를 생성자에서 끼워줘야 하겠는데 항상 있어야해
// 부모 리스트쪽에도 끼워주고

class GameManager;

class GameManagerObject : public GameObjectBase {
private:
    GameManager* pGameManager = nullptr;

public:
    GameManagerObject() = default;
    GameManagerObject(const GameManagerObject&) = delete;
    ~GameManagerObject() override;

    GameManager* GetGameManager() const { return pGameManager; }


    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;


    //void Render(HDC hdc) override;
};