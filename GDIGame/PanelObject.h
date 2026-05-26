#pragma once

#include "INC_Windows.h"
#include "MyGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

class Panel;

class PanelBitmap {

};

class PanelObject : public GameObjectBase, IDrawable, Transform {
private:
    Panel* pPanel = nullptr;
    PanelBitmap* pPanelBitmap = nullptr;

public:
    PanelObject() = default;
    PanelObject(const PanelObject&) = delete;
    ~PanelObject() override;

    Panel* GetPanel() const { return pPanel; }
    PanelBitmap* GetPanelBitmap() const { return pPanelBitmap; }


    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    //void Render(HDC hdc) override;


    void Draw(HDC hdc) override;


};