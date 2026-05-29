#pragma once

#include "Component.h"
#include "MyGameObject.h"
#include "Transform.h"

class IClickable;

class ClickableManager : public Component
{
private:
    static ClickableManager* instance;


    IClickable* curOver = nullptr;
    IClickable* interactingL = nullptr;
    IClickable* interactingR = nullptr;
    bool isLDown = false;
    bool isRDown = false;

public:
    ClickableManager() = delete;
    ClickableManager(GameObjectBase* gameObject) : Component(gameObject) {}

    ~ClickableManager() override = default;

    ClickableManager(const ClickableManager&) = delete;
    ClickableManager& operator=(const ClickableManager&) = delete;


    bool isActive = true;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // Own Logic

    // Singleton
    static ClickableManager* GetInstance();
    //static void DestroyInstance();


    // Input Events
    void HandleMouseMove(int mouseX, int mouseY);

    void HandleLDown(int mouseX, int mouseY);
    void HandleLUp(int mouseX, int mouseY);

    void HandleRDown(int mouseX, int mouseY);
    void HandleRUp(int mouseX, int mouseY);


    // Manager
    IClickable* GetClickable(GameObjectBase* pGameObject);
    bool TryGetClickable(GameObjectBase* pGameObject, IClickable*& pClickable);
};