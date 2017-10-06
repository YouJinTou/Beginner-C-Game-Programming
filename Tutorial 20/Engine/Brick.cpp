#include "Brick.h"

Brick::Brick(Graphics& gfx, Vec2 topLeft, float width, float height, Color color) :
	gfx(gfx),
	topLeft(topLeft),
	width(width),
	height(height),
	color(color) {
	isDestroyed = false;
}

void Brick::Draw() {
	if (!isDestroyed) {
		gfx.DrawRect(GetRect(), color);
	}
}

Rect Brick::GetRect() {
	return { topLeft, width, height };
}
