#pragma once

#include <random>
#include <string>

#include "Graphics.h"
#include "Square.h"
#include "Snake.h"
#include "SnakePart.h"
#include "Apple.h"
#include "Location.h"

class Board {
public:
	Board(Graphics& gfx);
	void Update(const std::string& command);
	void Draw();
private:
	const std::string StartCommand = "up";
	Graphics& gfx;
	std::mt19937 rand;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Snake snake;
	Apple apple;
	std::string command;

	void SetCommand(const std::string& command);
	bool AreColliding(
		Location loc1, 
		Location loc2, 
		int length1, 
		int height1, 
		int length2, 
		int height2);
};