/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	handleSteering();

	x_mobile += vx;
	y_mobile += vy;
	shouldChangeColor =
		this->wnd.kbd.KeyIsPressed(VK_CONTROL) ||
		isCollision(x_mobile, y_mobile, x_static, y_static, boxLength, boxLength) ||
		(x_mobile >= boundStartX && x_mobile <= boundEndX);
	shouldChangeShape = this->wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::ComposeFrame()
{
	drawBox(x_static, y_static, 0, 255, 255, false);

	if (shouldChangeColor) {
		drawBox(x_mobile, y_mobile, 255, 0, 0, shouldChangeShape);
	}
	else {
		drawBox(x_mobile, y_mobile, 0, 255, 0, shouldChangeShape);
	}
}

void Game::drawBox(int x, int y, int r, int g, int b, bool distort) {
	const Color c(r, g, b);
	const int d = distort ? 5 : 0;

	gfx.PutPixel(x + 0, y + d, c);
	gfx.PutPixel(x + 1, y + d, c);
	gfx.PutPixel(x + 2, y + d, c);
	gfx.PutPixel(x + 3, y + d, c);
	gfx.PutPixel(x + 4, y + d, c);
	gfx.PutPixel(x + 5, y + d, c);
	gfx.PutPixel(x + 6, y + d, c);
	gfx.PutPixel(x + 7, y + d, c);
	gfx.PutPixel(x + 8, y + d, c);
	gfx.PutPixel(x + 9, y + d, c);

	gfx.PutPixel(x + boxLength + d, y + 0, c);
	gfx.PutPixel(x + boxLength + d, y + 1, c);
	gfx.PutPixel(x + boxLength + d, y + 2, c);
	gfx.PutPixel(x + boxLength + d, y + 3, c);
	gfx.PutPixel(x + boxLength + d, y + 4, c);
	gfx.PutPixel(x + boxLength + d, y + 5, c);
	gfx.PutPixel(x + boxLength + d, y + 6, c);
	gfx.PutPixel(x + boxLength + d, y + 7, c);
	gfx.PutPixel(x + boxLength + d, y + 8, c);
	gfx.PutPixel(x + boxLength + d, y + 9, c);

	gfx.PutPixel(x + 0, y + boxLength + d, c);
	gfx.PutPixel(x + 1, y + boxLength + d, c);
	gfx.PutPixel(x + 2, y + boxLength + d, c);
	gfx.PutPixel(x + 3, y + boxLength + d, c);
	gfx.PutPixel(x + 4, y + boxLength + d, c);
	gfx.PutPixel(x + 5, y + boxLength + d, c);
	gfx.PutPixel(x + 6, y + boxLength + d, c);
	gfx.PutPixel(x + 7, y + boxLength + d, c);
	gfx.PutPixel(x + 8, y + boxLength + d, c);
	gfx.PutPixel(x + 9, y + boxLength + d, c);

	gfx.PutPixel(x + d, y + 0, c);
	gfx.PutPixel(x + d, y + 1, c);
	gfx.PutPixel(x + d, y + 2, c);
	gfx.PutPixel(x + d, y + 3, c);
	gfx.PutPixel(x + d, y + 4, c);
	gfx.PutPixel(x + d, y + 5, c);
	gfx.PutPixel(x + d, y + 6, c);
	gfx.PutPixel(x + d, y + 7, c);
	gfx.PutPixel(x + d, y + 8, c);
	gfx.PutPixel(x + d, y + 9, c);
}

void Game::handleSteering()
{
	if (this->wnd.kbd.KeyIsPressed(VK_LEFT)) {
		if (!goingLeft) {
			x_mobile -= vx;
			vx--;
			goingLeft = true;
		}
	}
	else {
		goingLeft = false;
	}

	if (this->wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		if (!goingRight)
		{
			x_mobile += vx;
			vx++;
			goingRight = true;
		}
	}
	else {
		goingRight = false;
	}

	if (this->wnd.kbd.KeyIsPressed(VK_UP)) {
		if (!goingUp)
		{
			y_mobile -= vy;
			vy--;
			goingUp = true;
		}
	}
	else {
		goingUp = false;
	}

	if (this->wnd.kbd.KeyIsPressed(VK_DOWN)) {
		if (!goingDown)
		{
			y_mobile += vy;
			vy++;
			goingDown = true;
		}
	}
	else {
		goingDown = false;
	}

	correctVelocityAfterScreenCollision(x_mobile, y_mobile, boxLength, maxX, maxY, vx, vy);
}

bool Game::isCollision(int x1, int y1, int x2, int y2, int length1, int length2)
{
	const int left1 = x1;
	const int left2 = x2;
	const int top1 = y1;
	const int top2 = y2;
	const int right1 = left1 + length1;
	const int right2 = left2 + length2;
	const int bottom1 = top1 + length1;
	const int bottom2 = top2 + length2;

	return
		left1 <= right2 &&
		right1 >= left2 &&
		top1 <= bottom2 &&
		bottom1 >= top2;
}

void Game::correctVelocityAfterScreenCollision(
	int x, int y, int length, int maxX, int maxY, int& vx, int& vy) {
	if (x + length + length / 2 >= maxX - 1) {
		vx = -1;
	}
	else if (x - length < 1) {
		vx = 1;
	}
	else if (y + length + length / 2 >= maxY - 1) {
		vy = -1;
	}
	else if (y - length < 1) {
		vy = 1;
	}
}