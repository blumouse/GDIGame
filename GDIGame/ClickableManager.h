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

private:
    std::vector<IClickable*> ppClickables;

    IClickable* curOver;
    IClickable* interacting;

private:
    ClickableManager();
    virtual ~ClickableManager();

    ClickableManager(const ClickableManager&) = delete;
    ClickableManager& operator=(const ClickableManager&) = delete;

public:
    static ClickableManager* GetInstance();
    static void DestroyInstance();

public:
    void HandleMouseMove(int mouseX, int mouseY);

    void HandleLDown(int mouseX, int mouseY);
    void HandleLUp(int mouseX, int mouseY);

    void HandleRDown(int mouseX, int mouseY);
    void HandleRUp(int mouseX, int mouseY);

private:
    IClickable* TryGetClickable(GameObjectBase* pObject);
};