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
private:
	static constexpr int Width = 100;
	static constexpr int Height = 30;
	static constexpr float Speed = 300.0f;
	Graphics& gfx;
	Vec2 topLeftPos;
	Color paddleColor{ Colors::Red };
	int leftBorder;
	int rightBorder;

	bool IsCollidingWithLeftWall() const;
	bool IsCollidingWithRightWall() const;
};