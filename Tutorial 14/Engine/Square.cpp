#include "Square.h"

Square::Square(Location loc, Color color) :
	loc(loc),
	color(color) {}

Location Square::GetLocation()
{
	return loc;
}

Color Square::GetColor()
{
	return color;
}
