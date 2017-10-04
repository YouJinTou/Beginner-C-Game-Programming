#pragma once

#include <string>

#include "SnakePart.h"
#include "Square.h"

class Snake {
public:
	Snake(int borderX, int borderY);
	~Snake();
public:
	bool shouldGrow;

	SnakePart* Get() const;
	void IncreaseSpeed();
	bool HasBittenTail() const;
	void Update(const std::string& command);
	int Size() const;
private:
	static constexpr int StartX = 300;
	static constexpr int StartY = 300;
	const int PWidth = Square::Width;
	const int PHeight = Square::Height;
	const std::string HeadDefaultDir = "up";
	const int borderX;
	const int borderY;
	int size = 1;
	double velocity = 2.0;
	SnakePart* parts;
	std::string currentDir;

	void Grow();
	void UpdateHead(std::string command);
	void UpdateBody();
	int RecalculateDim(int curr, const int& next);
	int CalculateUp(int currY);
	int CalculateDown(int currY);
	int CalculateLeft(int currX);
	int CalculateRight(int currX);
	bool Shifted(int& currX, int& currY, const int& nextX, const int& nextY);
};