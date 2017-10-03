#include "Snake.h"
#include "Square.h"

Snake::Snake() {
	parts = new SnakePart{ nullptr, StartX, StartY };
}

Snake::~Snake() {
	delete[] parts;
}

SnakePart* Snake::Get()
{
	return parts;
}

void Snake::Grow()
{
	SnakePart* newSnake = new SnakePart[size + 1];

	for (int i = 0; i < size; i++)
	{
		newSnake[i] = parts[i];
	}

	SnakePart currentTail = newSnake[size - 1];
	int x = currentTail.loc.x;
	int y = currentTail.loc.y;
	Location tailLoc =
		currentTail.dir == "up" ? Location{ x, y + Square::Height } :
		currentTail.dir == "down" ? Location{ x, y - Square::Height } :
		currentTail.dir == "left" ? Location{ x + Square::Width, y } :
		Location{ x - Square::Width, y };
	SnakePart newTail = { nullptr, tailLoc };
	currentTail.next = &newTail;
	newSnake[size] = newTail;

	delete[] parts;

	parts = newSnake;
	size++;
}

void Snake::Update(std::string command)
{
	if (command == "up" && currentDir != "down") {
		currentDir = "down";

		for (size_t i = 0; i < size; i++)
		{
		}
	}
}

int Snake::Size() const {
	return size;
}
