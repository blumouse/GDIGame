#pragma once

#include "MyGameObject.h"

class ClickableManager;

class ClickableManagerObject : public GameObjectBase
{
private:
    ClickableManager* pClickableManager = nullptr;

public:
    ClickableManagerObject();
    ClickableManagerObject(const ClickableManagerObject&) = delete;

    ~ClickableManagerObject() override = default;


    // GameObjectBase (Lifecycles)
    //void Awake() override;
    //void Start() override;
    //void Update(float deltaTime) override;
    //void FixedUpdate() override;

    //void OnDestroy() override;


    ClickableManager* GetClickableManager() const { return pClickableManager; }
};