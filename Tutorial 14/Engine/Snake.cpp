#include <cmath>

#include "Snake.h"
#include "Square.h"

Snake::Snake(int borderX, int borderY) :
	borderX(borderX), borderY(borderY) {
	parts = new SnakePart{ nullptr, StartX, StartY, HeadDefaultDir };
}

Snake::~Snake() {
	delete[] parts;
}

SnakePart* Snake::Get() const
{
	return parts;
}

void Snake::IncreaseSpeed()
{
	velocity += 0.5;
}

bool Snake::HasBittenTail() const {
	if (size <= 3) {
		return false;
	}

	int headX = parts[0].loc.x;
	int headY = parts[0].loc.y;

	for (int i = 3; i < size; i++)
	{
		int partX = parts[i].loc.x;
		int partY = parts[i].loc.y;
		bool hasBittenTail =
			headX < partX + PWidth &&
			headY < partY + PHeight &&
			headX + PWidth > partX &&
			headY + PHeight > partY;

		if (hasBittenTail) {
			return true;
		}
	}

	return false;
}

int Snake::Size() const {
	return size;
}

void Snake::Update(const std::string& command)
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
	int x = currentTail.loc.x;
	int y = currentTail.loc.y;
	Location newTailLoc =
		currentTail.dir == "up" ? Location{ x, y + PHeight } :
		currentTail.dir == "down" ? Location{ x, y - PHeight } :
		currentTail.dir == "left" ? Location{ x + PWidth, y } :
		Location{ x - PWidth, y };
	SnakePart newTail{ nullptr, newTailLoc, currentTail.dir };
	newSnake[size] = newTail;

	for (int i = size; i > 0; i--)
	{
		newSnake[i].next = &newSnake[i - 1];
	}

	//delete[] parts;

	parts = newSnake;
	size++;
}

void Snake::UpdateHead(std::string command)
{
	SnakePart& head = parts[0];

	if (command == "up" && !(currentDir == "down" || currentDir == "up")) {
		currentDir = "up";
		head.dir = "up";
	}
	else if (command == "down" && !(currentDir == "up" || currentDir == "down")) {
		currentDir = "down";
		head.dir = "down";
	}
	else if (command == "left" && !(currentDir == "right" || currentDir == "left")) {
		currentDir = "left";
		head.dir = "left";
	}
	else if (command == "right" && !(currentDir == "left" || currentDir == "right")) {
		currentDir = "right";
		head.dir = "right";
	}

	if (currentDir == "up") {
		head.loc.y = CalculateUp(head.loc.y);
	}
	else if (currentDir == "down") {
		head.loc.y = CalculateDown(head.loc.y);
	}
	else if (currentDir == "left") {
		head.loc.x = CalculateLeft(head.loc.x);
	}
	else if (currentDir == "right") {
		head.loc.x = CalculateRight(head.loc.x);
	}
}

void Snake::UpdateBody()
{
	int headIndex = 0;

	for (size_t p = size - 1; p > headIndex; p--)
	{
		SnakePart nextPart = *parts[p].next;
		int nextX = nextPart.loc.x;
		int nextY = nextPart.loc.y;
		int& currX = parts[p].loc.x;
		int& currY = parts[p].loc.y;

		if (Shifted(currX, currY, nextX, nextY)) {
			continue;
		}
		
		bool goUp =  currY - PHeight >= nextY;
		bool goDown = currY + PHeight <= nextY;
		bool goLeft = currX >= nextX + PWidth;
		bool goRight = currX + PWidth <= nextX;

		if (goUp) {
			currY = CalculateUp(currY);
			currX = RecalculateDim(currX, nextX);
		}
		else if (goDown) {
			currY = CalculateDown(currY);
			currX = RecalculateDim(currX, nextX);
		}
		else if (goLeft) {
			currX = CalculateLeft(currX);
			currY = RecalculateDim(currY, nextY);
		}
		else if (goRight) {
			currX = CalculateRight(currX);
			currY = RecalculateDim(currY, nextY);
		}
	}
}

int Snake::RecalculateDim(int curr, const int& next)
{
	return curr > next ? curr -= 1 :
		curr < next ? curr += 1 :
		curr;
}

int Snake::CalculateUp(int currY) {
	int y = (currY - velocity <= 0) ?
		borderY - PHeight :
		currY - velocity;

	return y;
}

int Snake::CalculateDown(int currY)
{
	int y = (currY + velocity >= borderY - PHeight) ?
		0 + PHeight :
		currY + velocity;

	return y;
}

int Snake::CalculateLeft(int currX)
{
	int x = (currX - velocity <= 0) ?
		borderX - PWidth :
		currX - velocity;
	
	return x;
}

int Snake::CalculateRight(int currX)
{
	int x = (currX + velocity >= borderX - PWidth) ?
		0 + PWidth :
		currX + velocity;

	return x;
}

bool Snake::Shifted(int& currX, int& currY, const int& nextX, const int& nextY)
{
	bool shifted = false;
	bool shiftUp = (std::abs(currY - nextY) >= 2 * PHeight) && (nextY >= borderY - 2 * PHeight); 
	bool shiftDown = (std::abs(currY - nextY) >= 2 * PHeight) && nextY <= 2 * PHeight;
	bool shiftLeft = (std::abs(currX - nextX) >= 2 * PWidth) && (nextX >= borderX - 2 * PWidth);
	bool shiftRight = (std::abs(currX - nextX) >= 2 * PWidth) && (nextX <= 2 * PWidth);

	if (shiftUp) {
		currY = CalculateUp(currY);
		currX = RecalculateDim(currX, nextX);
		shifted = true;
	}
	else if (shiftDown) {
		currY = CalculateDown(currY);
		currX = RecalculateDim(currX, nextX);
		shifted = true;
	}
	else if (shiftLeft) {
		currX = CalculateLeft(currX);
		currY = RecalculateDim(currY, nextY);
		shifted = true;
	}
	else if (shiftRight) {
		currX = CalculateRight(currX);
		currY = RecalculateDim(currY, nextY);
		shifted = true;
	}

	return shifted;
}
