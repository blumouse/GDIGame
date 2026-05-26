#pragma once

#include "INC_Windows.h"

class IDrawable {
public:
	IDrawable() = default;
	IDrawable(const IDrawable&) = delete;

	virtual ~IDrawable() = default;

	virtual void Draw(HDC hdc) = 0;
};