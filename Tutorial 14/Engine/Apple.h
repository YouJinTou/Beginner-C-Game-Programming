#pragma once

#include "Location.h"
#include "Colors.h"

class Apple {
public:
	Apple() = default;
	Apple(Location loc);
public:
	bool isEaten;

	void Update(Location loc);
	void Spawn(Location loc);
	Location GetLoc();
private:
	Location loc;
};