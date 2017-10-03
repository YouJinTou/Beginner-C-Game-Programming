#pragma once

#include "Location.h"
#include "Colors.h"

class Square {
public:
	static constexpr int Width = 8;
	static constexpr int Height = 6;

	Square() = default;
	Square(Location loc, Color color);
	Location GetLocation();
	Color GetColor();
private:
	Location loc;
	Color color;
};