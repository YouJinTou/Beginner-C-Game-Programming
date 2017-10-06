#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Vec2.h"
#include "Rect.h"

class Brick {
public:
	Brick(Graphics& gfx, Vec2 topLeft, float width, float height, Color color);
	void Draw();
	Rect GetRect();
	bool isDestroyed;
private:
	Graphics& gfx;
	Vec2 topLeft;
	float width;
	float height;
	Color color;
	Rect rect;
};