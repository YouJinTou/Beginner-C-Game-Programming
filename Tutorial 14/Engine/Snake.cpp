#include "Snake.h"
#include "Square.h"

Snake::Snake() {
	parts = new SnakePart{ nullptr, StartX, StartY, HeadDefaultDir };
}

Snake::~Snake() {
	delete[] parts;
}

SnakePart* Snake::Get()
{
	return parts;
}

int Snake::Size() const {
	return size;
}

void Snake::Update(std::string command)
{
	if (shouldGrow) {
		Grow();
	}

	UpdateHead(command);
	UpdateBody();	
}

void Snake::Grow()
{
	SnakePart* newSnake = new SnakePart[size + 1];

	for (int i = 0; i < size; i++)
	{
		newSnake[i] = parts[i];
	}

	SnakePart currentTail = newSnake[size - 1];
	SnakePart* ptrCurrentTail = &newSnake[size - 1];
	int x = currentTail.loc.x;
	int y = currentTail.loc.y;
	Location newTailLoc =
		currentTail.dir == "up" ? Location{ x, y + Square::Height } :
		currentTail.dir == "down" ? Location{ x, y - Square::Height } :
		currentTail.dir == "left" ? Location{ x + Square::Width, y } :
		Location{ x - Square::Width, y };
	SnakePart newTail = { ptrCurrentTail, newTailLoc, currentTail.dir };
	newSnake[size] = newTail;

	//delete[] parts;

	parts = newSnake;
	size++;
}

void Snake::UpdateHead(std::string command)
{
	SnakePart& head = parts[0];

	if (command == "up" && !(currentDir == "down" || currentDir == "up")) {
		currentDir = "up";
		head.loc.y -= 1;
		head.dir = "up";
	}
	else if (command == "down" && !(currentDir == "up" || currentDir == "down")) {
		currentDir = "down";
		head.loc.y += 1;
		head.dir = "down";
	}
	else if (command == "left" && !(currentDir == "right" || currentDir == "left")) {
		currentDir = "left";
		head.loc.x -= 1;
		head.dir = "left";
	}
	else if (command == "right" && !(currentDir == "left" || currentDir == "right")) {
		currentDir = "right";
		head.loc.x += 1;
		head.dir = "right";
	}

	if (currentDir == "up") {
		head.loc.y -= 1;
	}
	else if (currentDir == "down") {
		head.loc.y += 1;
	}
	else if (currentDir == "left") {
		head.loc.x -= 1;
	}
	else if (currentDir == "right") {
		head.loc.x += 1;
	}
}

void Snake::UpdateBody()
{
	int headIndex = 0;

	for (size_t p = size - 1; p > headIndex; p--)
	{
		SnakePart nextPart = *parts[p].next;
		std::string nextDir = nextPart.dir;
		int nextX = nextPart.loc.x;
		int nextY = nextPart.loc.y;
		int& currX = parts[p].loc.x;
		int& currY = parts[p].loc.y;
		bool goLeft = currX < nextX + Square::Width;
		bool goRight = currX + Square::Width > nextX;
		bool goUp = currY > nextY + Square::Height;
		bool goDown = currY + Square::Height < nextY ;

		currX = goLeft ? --currX :
			goRight ? ++currX : currX;
		currY = goUp ? --currY :
			goDown ? ++currY : currY;
	}
}
