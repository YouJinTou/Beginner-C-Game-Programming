#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx) {
	InitSquares();
}

void Board::Update()
{
}

void Board::Draw() {
	SnakePart* snakeParts = snake.Get();

	for (int i = 0; i < snake.Size(); i++)
	{
		SnakePart part = snakeParts[i];
		Location loc = part.loc;

		gfx.DrawRect(
			loc.x, loc.y, loc.x + Square::Width, loc.y + Square::Height, Colors::White);
	}

	Location appleLoc = apple.GetLoc();

	gfx.DrawRect(
		appleLoc.x, appleLoc.y, appleLoc.x + Square::Width, appleLoc.y + Square::Height, Colors::Red);
}

void Board::InitSquares() {
	int square = 0;

	for (int r = 0; r < SquaresX; r++)
	{
		for (int c = 0; c < SquaresY; c++)
		{
			squares[square] = Square({ r, c }, Colors::Black);
			square++;
		}
	}
}