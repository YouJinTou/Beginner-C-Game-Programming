#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx),
	walls(SetWalls()),
	paddle(Paddle(gfx, (int)LeftWall.Width(), (int)RightWall.X())),
	ball(gfx, paddle, walls, bricks) {
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

	if (ball.IsLost()) {
		lives--;

		if (!IsLost()) {
			paddle.Reset();
			ball.SetRelativeToPaddle();
		}
	}
}

void Board::Draw() {
	DrawBorder();
	DrawBricks();
	DrawLives();
	paddle.Draw();
	ball.Draw();
}

bool Board::IsLost() {
	return lives == 0;
}

void Board::DrawBorder() const {
	gfx.DrawRect(LeftWall, WallCollor);
	gfx.DrawRect(TopWall, WallCollor);
	gfx.DrawRect(RightWall, WallCollor);
}

void Board::DrawBricks() {
	int colorCounter = 0;

	for (auto& brick : bricks) {
		brick.Draw();
	}
}

void Board::DrawLives() const {
	int x = 15;
	int y = gfx.ScreenHeight - 20;
	int width = x + 5;
	int height = y + 15;
	int offset = 5;

	for (size_t i = 0; i < lives; i++)
	{
		gfx.DrawRect(x, y, width + x, height, Colors::Gray);

		x += width + offset;
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
		(gfx.ScreenWidth - 2 * BorderSize - 2 * BorderPadding - 10 * marginRight) /
		BrickCols;
	float height = 10;
	float x = 0.0f;
	float y = BorderSize + paddingTop + BorderPadding;
	int colorCounter = 0;

	for (size_t row = 0; row < BrickRows; row++)
	{
		x = BorderPadding + BorderSize;
		y += height + marginTop;

		for (size_t col = 0; col < BrickCols; col += 1)
		{
			colorCounter = (colorCounter >= MaxColors) ? 0 : colorCounter;
			bricks.push_back(Brick(gfx, { x, y }, x + width, y + height, brickColors[colorCounter]));

			x += width + marginRight;
			colorCounter++;
		}
	}
}
