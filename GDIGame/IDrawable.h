#pragma once

#include "INC_Windows.h"

class IDrawable {
protected:
	IDrawable();
	IDrawable(const IDrawable&) = delete;

public:
	virtual ~IDrawable() = default;

	virtual void Draw(HDC hdc) = 0;
};