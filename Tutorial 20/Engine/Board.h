#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "Rect.h"

class Board {
public:
	Board(Graphics& gfx);
	void Update(const Keyboard & kb);
	void Draw() const;
private:
	Graphics& gfx;
	static constexpr int BorderPadding = 10;
	const int Width = gfx.ScreenWidth - 2 * BorderPadding;
	const int Height = gfx.ScreenHeight - BorderPadding;
	const Vec2 TopLeft{ BorderPadding, BorderPadding };
	const Rect LeftWall{ 0, 0, BorderPadding, gfx.ScreenHeight };
	const Rect TopWall{ BorderPadding, 0, gfx.ScreenWidth - BorderPadding, BorderPadding };
	const Rect RightWall{ gfx.ScreenWidth - BorderPadding, 0, gfx.ScreenWidth, gfx.ScreenHeight };
	const Color WallCollor{ Colors::LightGray };

	void DrawBorder() const;
};
