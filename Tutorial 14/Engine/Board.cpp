#include "Board.h"

Board::Board(Graphics & gfx) :
	gfx(gfx),
	rand(std::random_device()()),
	xDist(0, gfx.ScreenWidth),
	yDist(0, gfx.ScreenHeight),
	apple({ xDist(rand), yDist(rand) }) {
	InitSquares();
}


void Board::Update(const std::string& command)
{
	bool areColliding = AreColliding(
		snake.Get()[0].loc, apple.GetLoc(), Square::Width,
		Square::Height, Square::Width, Square::Height);
	apple.isEaten = areColliding;
	snake.shouldGrow = areColliding;

	SetCommand(command);
	snake.Update(this->command);

	if (apple.isEaten) {
		apple.Update(Location{ xDist(rand), yDist(rand) });
	}
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

void Board::SetCommand(const std::string& command)
{
	this->command = command == "continue" ?
		this->command == "" ? StartCommand : this->command :
		command;
}

bool Board::AreColliding(
	Location loc1, Location loc2, int length1,
	int height1, int length2, int height2) {
	return
		loc1.x <= loc2.x + length2 &&
		loc1.y <= loc2.y + height2 &&
		loc1.x + length1 >= loc2.x &&
		loc1.y + height1 >= loc2.y;
}
