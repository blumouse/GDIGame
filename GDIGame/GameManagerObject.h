#pragma once
#include "INC_Windows.h"
#include "GameObject.h"

class Component;

class GameManagerObject : public GameObjectBase {
private:
	Component* pGameManager = nullptr;

public:
    GameManagerObject(const GameManagerObject&) = delete;
    GameManagerObject(ObjectType type) : GameObjectBase(type) {}
    ~GameManagerObject() override;


    void Update(float deltaTime) override;
    void Render(HDC hdc) override;
};