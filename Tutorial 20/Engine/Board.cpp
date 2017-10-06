#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx),
	walls(SetWalls()),
	paddle(Paddle(gfx, (int)LeftWall.Width(), (int)RightWall.X())),
	ball(gfx, paddle, walls) {
	InitBricks();
}

void Board::Update(const Keyboard & kb, float dt) {
	std::string cmd =
		kb.KeyIsPressed(VK_LEFT) ? "left" :
		kb.KeyIsPressed(VK_RIGHT) ? "right" :
		kb.KeyIsPressed(VK_SPACE) ? "launch" :
		"";

	paddle.Update(cmd, dt);
	ball.Update(dt);

	if (ball.isLost) {
		isLost = true;
	}
}

void Board::Draw() const {
	DrawBorder();
	DrawBricks();
	paddle.Draw();
	ball.Draw();
}

void Board::DrawBorder() const {
	gfx.DrawRect(LeftWall, WallCollor);
	gfx.DrawRect(TopWall, WallCollor);
	gfx.DrawRect(RightWall, WallCollor);
}

void Board::DrawBricks() const {
	int colorCounter = 0;

	for (Rect brick : bricks) {
		colorCounter = (colorCounter >= MaxColors) ? 0 : colorCounter;

		gfx.DrawRect(brick, brickColors[colorCounter]);

		colorCounter++;
	}
}

std::vector<Rect> Board::SetWalls() {
	std::vector<Rect> walls;

	walls.push_back(LeftWall);
	walls.push_back(TopWall);
	walls.push_back(RightWall);

	return walls;
}

void Board::InitBricks() {
	float marginRight = 5;
	float marginTop = 5;
	float paddingTop = 30;
	float width =
		(gfx.ScreenWidth - 2 * BorderPadding - 10 * marginRight) /
		BrickCols;
	float height = 10;
	float x = 0.0f;
	float y = BorderPadding + paddingTop;
	int brick = 0;

	for (size_t row = 0; row < BrickRows; row++)
	{
		x = BorderPadding;
		y += height + marginTop;

		for (size_t col = 0; col < BrickCols; col += 1)
		{
			bricks[brick] = Rect({ x, y }, x + width, y + height);
			brick++;

			x += width + marginRight;
		}
	}
}
