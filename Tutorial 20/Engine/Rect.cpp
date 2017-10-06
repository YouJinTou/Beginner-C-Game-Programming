#include "Rect.h"

Rect::Rect(float topX, float topY, float width, float height) :
	topLeft({ topX, topY }),
	width(width),
	height(height)
{
}

Rect::Rect(const Vec2 & topLeft, float width, float height) :
	Rect::Rect(topLeft.x, topLeft.y, width, height)
{
}

float Rect::X() {
	return topLeft.x;
}

float Rect::Y() {
	return topLeft.y;
}

float Rect::Width() {
	return width;
}

float Rect::Height() {
	return height;
}
