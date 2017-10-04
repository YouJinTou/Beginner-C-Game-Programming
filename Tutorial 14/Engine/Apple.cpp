#include "Apple.h"

Apple::Apple(Location loc) :
	loc(loc) {}

void Apple::Update(Location loc)
{
	if (isEaten) {
		Spawn(loc);
	}
}

void Apple::Spawn(Location loc)
{
	this->loc = loc;
}

Location Apple::GetLoc()
{
	return loc;
}
