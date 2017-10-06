#pragma once

#include "Graphics.h"
#include "Keyboard.h"

class Board {
public:
	Board(Graphics& gfx);
	void Update(const Keyboard & kb);
	void Draw();
private:
	Graphics& gfx;
};
