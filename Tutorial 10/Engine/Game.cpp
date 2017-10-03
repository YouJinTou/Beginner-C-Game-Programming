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
	ProcessInput();
}

void Game::ComposeFrame()
{
	DrawRect(rectX, rectY);
}

void Game::ProcessInput()
{
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		rectY = (rectY - velocity > 0) ? rectY -= velocity : rectY;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		rectY = (rectY + velocity < gfx.ScreenHeight - rectHeight) ? rectY += velocity : rectY;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		rectX = (rectX - velocity > 0) ? rectX -= velocity : rectX;
	}

	if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		rectX = (rectX + velocity < gfx.ScreenWidth - rectWidth) ? rectX += velocity : rectX;
	}

	if (wnd.kbd.KeyIsPressed('W') && rectY > 0) {
		rectHeight = (rectY + rectHeight < gfx.ScreenHeight) ? ++rectHeight : rectHeight;
		rectY--;
	}

	if (wnd.kbd.KeyIsPressed('S') && rectY < gfx.ScreenHeight - rectHeight) {
		rectHeight = (rectY + rectHeight < gfx.ScreenHeight) ? ++rectHeight : rectHeight;
	}

	if (wnd.kbd.KeyIsPressed('A') && rectX > 0) {
		rectWidth = (rectX + rectWidth > 0) ? ++rectWidth : rectWidth;
		rectX--;
	}

	if (wnd.kbd.KeyIsPressed('D') && rectX < gfx.ScreenWidth - rectWidth) {
		rectWidth = (rectX + rectWidth > 0) ? ++rectWidth : rectWidth;
	}
}

void Game::DrawRect(const int x, const int y)
{
	int width = x;

	for (size_t i = 0; i < rectWidth; i++)
	{
		int height = y;

		gfx.PutPixel(width, height, 255, 255, 255);
		
		for (size_t j = 0; j < rectHeight; j++)
		{
			gfx.PutPixel(width, height, 255, 255, 255);

			height++;
		}

		width++;
	}
}