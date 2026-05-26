#pragma once

#include <vector>

#include "Component.h"
#include "MyGameObject.h"
#include "Transform.h"

class IClickable;

class ClickableManager : public Component
{
private:
    static ClickableManager* instance;

    std::vector<IClickable*> ppClickables;

    IClickable* curOver;
    IClickable* interacting;


public:
    ClickableManager() = delete;
    ClickableManager(GameObjectBase* gameObject);

    ~ClickableManager() override;

    ClickableManager(const ClickableManager&) = delete;
    ClickableManager& operator=(const ClickableManager&) = delete;


    static ClickableManager* GetInstance();
    static void DestroyInstance();


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // Input Events
    void HandleMouseMove(int mouseX, int mouseY);

    void HandleLDown(int mouseX, int mouseY);
    void HandleLUp(int mouseX, int mouseY);

    void HandleRDown(int mouseX, int mouseY);
    void HandleRUp(int mouseX, int mouseY);


    IClickable* TryGetClickable(GameObjectBase* pObject);
};