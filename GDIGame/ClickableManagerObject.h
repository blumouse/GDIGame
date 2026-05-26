#pragma once

#include "MyGameObject.h"

class ClickableManager;

class ClickableManagerObject : public GameObjectBase
{
private:
    ClickableManager* pClickableManager;

public:
    ClickableManagerObject();
    ClickableManagerObject(const ClickableManagerObject&) = delete;

    ~ClickableManagerObject() override;

    ClickableManager* GetClickableManager() const { return pClickableManager; }


    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;
};