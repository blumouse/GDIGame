#pragma once
#pragma once
#include "INC_Windows.h"
#include "GameObject.h"
#include "IDrawable.h"

class Component;

class PanelObject : public GameObjectBase, IDrawable {
private:
    Component* pPanel = nullptr;
    Component* pPanelBitmap = nullptr;

public:
    PanelObject(const PanelObject&) = delete;
    PanelObject(ObjectType type) : GameObjectBase(type) {}
    ~PanelObject() override;


    void Update(float deltaTime) override;
    void Render(HDC hdc) override;


    void Draw() override;
};