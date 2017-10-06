#pragma once

#include <string>

#include "Graphics.h"
#include "Vec2.h"
#include "Colors.h"
#include "Rect.h"
#include "Colors.h"

class Paddle {
public:
	Paddle(Graphics& gfx, int leftBorder, int rightBorder);
	void Update(const std::string& command, const float dt);
	void Draw() const;
	Rect GetRect() const;
	Vec2 Center() const;
	int GetWidth() const;
	int GetHeight() const;
	bool BallLaunched() const;
	void Reset();
private:
	static constexpr int Width = 100;
	static constexpr int Height = 15;
	static constexpr int WingsLength = 15;
	static constexpr float Speed = 300.0f;
	static constexpr Color paddleColor{ Colors::Red };
	static constexpr Color wingsColor{ Colors::Green };
	Graphics& gfx;
	Vec2 topLeft;
	int leftBorder;
	int rightBorder;
	float startX;
	float startY;
	bool ballLaunched = false;

	bool IsCollidingWithLeftWall() const;
	bool IsCollidingWithRightWall() const;
};