#pragma once

#include "Location.h"
#include "Colors.h"

class Apple {
public:
	Apple() = default;
	Apple(Location loc);
	void Spawn();
	bool IsEaten();
	Location GetLoc();
private:
	Location loc;
};