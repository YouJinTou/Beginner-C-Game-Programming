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
	static constexpr int SquaresX = 100;
	static constexpr int SquaresY = 60;
	const std::string StartCommand = "up";
	Graphics& gfx;
	std::mt19937 rand;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Square squares[SquaresX * SquaresY];
	Snake snake;
	Apple apple;
	std::string command;

	void InitSquares();
	void SetCommand(const std::string& command);
	bool AreColliding(
		Location loc1, 
		Location loc2, 
		int length1, 
		int height1, 
		int length2, 
		int height2);
};