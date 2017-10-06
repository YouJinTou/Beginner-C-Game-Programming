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
	static constexpr int BrickCols = 10;
	static constexpr int BrickRows = 6;
	static constexpr int MaxColors = 4;
	Color brickColors[4]{ Colors::Red, Colors::Green, Colors::Cyan, Colors::Yellow };
	Rect LeftWall{ 0.0f, 0.0f, BorderPadding, (float)gfx.ScreenHeight };
	Rect TopWall{ BorderPadding, 0, (float)(gfx.ScreenWidth - BorderPadding), BorderPadding };
	Rect RightWall{ gfx.ScreenWidth - BorderPadding, 0.0f, (float)gfx.ScreenWidth, (float)gfx.ScreenHeight };
	std::vector<Rect> walls;	
	Rect bricks[BrickRows * BrickCols];
	Paddle paddle;
	Ball ball;

	void DrawBorder() const;
	void DrawBricks() const;
	std::vector<Rect> SetWalls();
	void InitBricks();
};
