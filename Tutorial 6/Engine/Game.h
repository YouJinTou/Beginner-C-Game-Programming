/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void drawBox(int x, int y, int r, int g, int b, bool distort);
	void handleSteering();
	bool isCollision(int x1, int y1, int x2, int y2, int length1, int length2);
	void correctVelocityAfterScreenCollision(
		int x, int y, int length, int maxX, int maxY, int& vx, int& vy);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	const int boxLength = 10;
	const int maxX = gfx.ScreenWidth;
	const int maxY = gfx.ScreenHeight;
	const int boundStartX = 300;
	const int boundEndX = 450;
	bool shouldChangeShape;
	bool shouldChangeColor;
	int x_mobile = 400;
	int y_mobile = 400;
	int x_static = 200;
	int y_static = 200;
	int vx = 1;
	int vy = 1;
	bool goingUp;
	bool goingDown;
	bool goingLeft;
	bool goingRight;
	/********************************/
};