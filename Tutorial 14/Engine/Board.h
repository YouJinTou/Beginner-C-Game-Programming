#pragma once

#include "Graphics.h"
#include "Square.h"
#include "Snake.h"
#include "SnakePart.h"
#include "Apple.h"
#include "Location.h"

class Board {
public:
	Board(Graphics& gfx);
	void Update();
	void Draw();
private:
	static constexpr int SquaresX = 100;
	static constexpr int SquaresY = 60;
	Graphics& gfx;
	Square squares[SquaresX * SquaresY];
	Snake snake;
	Apple apple;

	void InitSquares();
};