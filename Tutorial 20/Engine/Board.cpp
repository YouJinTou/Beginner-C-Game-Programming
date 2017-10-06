#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx),
	walls(SetWalls()),
	paddle(Paddle(gfx, (int)LeftWall.Width(), (int)RightWall.X())),
	ball(gfx, paddle, walls) {	
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
	paddle.Draw();
	ball.Draw();
}

void Board::DrawBorder() const {
	gfx.DrawRect(LeftWall, WallCollor);
	gfx.DrawRect(TopWall, WallCollor);
	gfx.DrawRect(RightWall, WallCollor);
}

std::vector<Rect> Board::SetWalls() {
	std::vector<Rect> walls;

	walls.push_back(LeftWall);
	walls.push_back(TopWall);
	walls.push_back(RightWall);

	return walls;
}
