#pragma once

#include <string>

#include "SnakePart.h"

class Snake {
public:
	Snake();
	~Snake();
	SnakePart* Get();
	void Grow();
	void Update(std::string command);
	int Size() const;
private:
	static constexpr int StartX = 300;
	static constexpr int StartY = 300;
	int size = 1;
	SnakePart* parts;
	std::string currentDir;
	int turningX;
	int turningY;
};