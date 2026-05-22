#pragma once

class IDrawable {
public:
	// IDrawable();
	virtual ~IDrawable() = default;

	virtual void Draw() = 0;
};