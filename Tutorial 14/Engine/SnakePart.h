#pragma once

#include <string>

#include "Location.h"

struct SnakePart {	
	SnakePart* next;
	Location loc;
	std::string dir;
};