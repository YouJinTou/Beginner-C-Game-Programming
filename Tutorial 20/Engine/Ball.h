#pragma once

#include "Graphics.h"
#include "Paddle.h"
#include "Rect.h"

class Ball {
public:
	Ball(Graphics& gfx, Paddle& paddle);
	void Update();
	void Draw() const;
private:
	static constexpr float Radius = 10.0f;
	float speed = 200.0f;
	Graphics& gfx;
	Paddle& paddle;
	Vec2 topLeft;
	Rect rect;

	Vec2 Center() const;
	void SetRelativeToPaddle();
};