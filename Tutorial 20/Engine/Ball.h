#pragma once

#include <vector>

#include "Graphics.h"
#include "Paddle.h"
#include "Rect.h"

class Ball {
public:
	Ball(Graphics& gfx, const Paddle& paddle, const std::vector<Rect>& walls);
	void Update(float dt);
	void Draw() const;
private:
	static constexpr float Radius = 7.0f;
	static constexpr int PaddleXSegments = 7;
	const float speed = 200.0f;
	const float PaddleXTouchVelocityValues[PaddleXSegments]
		{ -2.5f * speed, -2 * speed, -1 * speed, 0, 1 * speed, 2 * speed, 2.5f * speed };
	const std::vector<Rect>& walls;
	const Paddle& paddle;
	Graphics& gfx;
	Vec2 topLeft;
	Vec2 velocity;
	bool justLaunched = false;

	Vec2 Center() const;
	Rect GetRect() const;
	void SetRelativeToPaddle();
	void HandleLaunch();
	void HandleWallCollision();
	void HandlePaddleCollision();
	bool IsCollidingWithLeftWall() const;
	bool IsCollidingWithTopWall() const;
	bool IsCollidingWithRightWall() const;
	bool IsCollidingWithPaddle() const;

};