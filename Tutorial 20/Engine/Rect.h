#pragma once

#include "Vec2.h"

class Rect {
public:
	Rect() = default;
	Rect(float topX, float topY, float width, float height);
	Rect(const Vec2& topLeft, float width, float height);
	float X();
	float Y();
	float Width();
	float Height();
private:
	Vec2 topLeft;
	float width;
	float height;
};