#pragma once

class IClickable
{
public:
    virtual ~IClickable() = default;


    virtual void OnMouseEnter() = 0;
    virtual void OnMouseExit() = 0;

    virtual void OnLDown() = 0;
    virtual void OnLComplete() = 0;
    virtual void OnLCancel() = 0;

    virtual void OnRDown() = 0;
    virtual void OnRComplete() = 0;
    virtual void OnRCancel() = 0;
};