#pragma once

#include <vector>

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "Rect.h"
#include "Paddle.h"
#include "Ball.h"

class Board {
public:
	Board(Graphics& gfx);
	void Update(const Keyboard& kb, const float dt);
	void Draw() const;

	bool isLost = false;
private:
	Graphics& gfx;
	static constexpr float BorderPadding = 10.0f;
	const Vec2 TopLeft{ BorderPadding, BorderPadding };
	const Color WallCollor{ Colors::LightGray };
	Rect LeftWall{ 0.0f, 0.0f, BorderPadding, (float)gfx.ScreenHeight };
	Rect TopWall{ BorderPadding, 0, (float)(gfx.ScreenWidth - BorderPadding), BorderPadding };
	Rect RightWall{ gfx.ScreenWidth - BorderPadding, 0.0f, (float)gfx.ScreenWidth, (float)gfx.ScreenHeight };
	std::vector<Rect> walls;
	Paddle paddle;
	Ball ball;

	void DrawBorder() const;
	std::vector<Rect> SetWalls();
};
