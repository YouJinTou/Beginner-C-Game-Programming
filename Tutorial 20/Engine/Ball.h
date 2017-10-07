#pragma once

#include <vector>

#include "Graphics.h"
#include "Paddle.h"
#include "Rect.h"
#include "Brick.h"
#include "Sound.h"

class Ball {
public:
	Ball(
		Graphics& gfx, 
		const Paddle& paddle, 
		const std::vector<Rect>& walls, 
		std::vector<Brick>& bricks);
	void Update(float dt);
	void Draw() const;
	void SetRelativeToPaddle();
	bool IsLost() const;
private:
	static constexpr float Radius = 7.0f;
	static constexpr int PaddleXSegments = 7;
	const float speed = 250.0f;
	const float PaddleXTouchVelocityValues[PaddleXSegments]
		{ -2.5f * speed, -2 * speed, -1 * speed, 0, 1 * speed, 2 * speed, 2.5f * speed };
	const std::vector<Rect>& walls;
	const Paddle& paddle;
	const float paddleReboudFactor = 7.5f;
	std::vector<Brick>& bricks;
	Graphics& gfx;
	Vec2 topLeft;
	Vec2 velocity;
	bool justLaunched = false;
	Sound onHitPaddle = Sound(L"Sounds//arkpad.wav");
	Sound onHitBrick = Sound(L"Sounds//arkbrick.wav");

	Vec2 Center() const;
	Rect GetRect() const;
	void HandleLaunch();
	void HandleWallCollision();
	void HandlePaddleCollision();
	void HandleBrickCollision();
	void DoBrickCollision(Brick* brick);
	bool IsCollidingWithLeftWall() const;
	bool IsCollidingWithTopWall() const;
	bool IsCollidingWithRightWall() const;
	bool IsCollidingWithPaddle() const;
};