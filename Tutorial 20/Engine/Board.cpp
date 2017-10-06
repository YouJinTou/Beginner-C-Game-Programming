#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx) {
}

void Board::Update(const Keyboard & kb) {
}

void Board::Draw() const {
	DrawBorder();
}

void Board::DrawBorder() const {
	gfx.DrawRect(LeftWall, WallCollor);
	gfx.DrawRect(TopWall, WallCollor);
	gfx.DrawRect(RightWall, WallCollor);
}

