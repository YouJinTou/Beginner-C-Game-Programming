#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx),
	paddle(Paddle(gfx, (int)LeftWall.Width(), (int)RightWall.X())) {
}

void Board::Update(const Keyboard & kb, float dt) {
	paddle.Update(kb.KeyIsPressed(VK_LEFT) ? "left" : kb.KeyIsPressed(VK_RIGHT) ? "right" : "", dt);
}

void Board::Draw() const {
	DrawBorder();
	paddle.Draw();
}

void Board::DrawBorder() const {
	gfx.DrawRect(LeftWall, WallCollor);
	gfx.DrawRect(TopWall, WallCollor);
	gfx.DrawRect(RightWall, WallCollor);
}

