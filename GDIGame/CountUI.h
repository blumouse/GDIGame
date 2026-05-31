#pragma once

#include "Component.h"

class CountUIBitmap;

class CountUI : public Component
{
    friend class CountUIBitmap;
    friend class GameManager;

private:
    CountUIBitmap* countUIBitmap = nullptr;

    int curNumber = 0;

public:
    CountUI() = delete;
    CountUI(GameObjectBase* gameObject) : Component(gameObject) {}

    ~CountUI() override = default;


    // Component (Lifecycles)
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;
    void FixedUpdate() override;

    void OnDestroy() override;


    // Own Logic

    void SetCount(int num);
};

