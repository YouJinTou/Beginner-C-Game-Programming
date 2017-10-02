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
	void InitEnemies();
	void HandleInput();
	void SetEnemyTrajectory(int& x, int& y, int& velocityX, int& velocityY);
	bool HaveCollided(int x1, int y1, int length1, int x2, int y2, int length2);
	void DrawHero(int x, int y);
	void DrawEnemy(int x, int y, bool isDead);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	const int maxLength = 20;
	const int heroAcceleration = 2;
	const int heroLength = 36;
	const int enemyLength = 20;
	const int heroWidthBuffer = 50;
	const int heroHeightBuffer = 50;
	const int enemyWidthBuffer = 30;
	const int enemyHeightBuffer = 20;
	int heroX = gfx.ScreenWidth / 2;
	int heroY = gfx.ScreenHeight / 2;
	int enemy1X;
	int enemy1Y;
	int enemy2X;
	int enemy2Y;
	int enemy3X;
	int enemy3Y;
	int enemy1VelocityX = -3;
	int enemy1VelocityY = -3;
	int enemy2VelocityX = 3;
	int enemy2VelocityY = 3;
	int enemy3VelocityX = -3;
	int enemy3VelocityY = -3;
	bool enemy1Dead;
	bool enemy2Dead;
	bool enemy3Dead;
	/********************************/
};