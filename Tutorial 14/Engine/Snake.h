#pragma once

#include <string>

#include "SnakePart.h"

class Snake {
public:
	Snake();
	~Snake();
public:
	bool shouldGrow;

	SnakePart* Get();
	void Update(std::string command);
	int Size() const;
private:
	static constexpr int StartX = 300;
	static constexpr int StartY = 300;
	const std::string HeadDefaultDir = "up";
	int size = 1;
	SnakePart* parts;
	std::string currentDir;

	void Grow();
	void UpdateHead(std::string command);
	void UpdateBody();
};