#pragma once

#include "MyGameObject.h"


// 컴포넌트를 생성자에서 끼워줘야 하겠는데 항상 있어야해
// 부모 리스트쪽에도 끼워주고

class GameManager;

class GameManagerObject : public GameObjectBase {
private:
    GameManager* pGameManager = nullptr;

public:
    GameManagerObject();
    GameManagerObject(const GameManagerObject&) = delete;

    ~GameManagerObject() override = default;


    // GameObjectBase (Lifecycles)
    //void Awake() override;
    //void Start() override;
    //void Update(float deltaTime) override;
    //void FixedUpdate() override;

    //void OnDestroy() override;


    GameManager* GetGameManager() const { return pGameManager; }
};