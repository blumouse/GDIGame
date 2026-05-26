#pragma once

#include "Transform.h"

class IClickable
{
public:
    virtual ~IClickable() = default;

public:
    virtual Transform* GetTransform() const = 0;

public:
    virtual void OnMouseEnter() = 0;
    virtual void OnMouseExit() = 0;

    virtual void OnLDown() = 0;
    virtual void OnLComplete() = 0;
    virtual void OnLCancel() = 0;

    virtual void OnRDown() = 0;
    virtual void OnRComplete() = 0;
    virtual void OnRCancel() = 0;
};