#pragma once

#include "Component.h"
#include "RenderHelp.h"


namespace renderHelp
{
    class BitmapInfo;
}


class PanelBitmap : public Component
{
    using BitmapInfo = renderHelp::BitmapInfo;

public:
    PanelBitmap() = delete;
    PanelBitmap(GameObjectBase* gameObject) : Component(gameObject) {}

    ~PanelBitmap() override = default;

    // 비트맵 정보 리소스에서 가져오기...
};