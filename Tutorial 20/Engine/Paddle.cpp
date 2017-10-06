#include "Paddle.h"

Paddle::Paddle(Graphics& gfx, int leftBorder, int rightBorder) :
	gfx(gfx), 
	leftBorder(leftBorder),
	rightBorder(rightBorder) {
	float startX = (gfx.ScreenWidth / 2) - Width / 2;
	float startY = gfx.ScreenHeight - Height;
	topLeftPos = Vec2(startX, startY);
}

void Paddle::Update(const std::string& command, const float dt) {
	if (command == "left") {
		topLeftPos.x = IsCollidingWithLeftWall() ? leftBorder : topLeftPos.x - (dt * Speed);
	}
	else if (command == "right") {
		topLeftPos.x = IsCollidingWithRightWall() ? rightBorder - Width : topLeftPos.x + (dt * Speed);
	}
}

void Paddle::Draw() const {
	gfx.DrawRect(GetRect(), paddleColor);
}

Rect Paddle::GetRect() const {
	Rect rect{ topLeftPos, topLeftPos.x + Width, topLeftPos.y + Height };

	return rect;
}

bool Paddle::IsCollidingWithLeftWall() const
{
	Rect paddle = GetRect();

	return paddle.X() <= leftBorder;
}


bool Paddle::IsCollidingWithRightWall() const
{
	Rect paddle = GetRect();

	return paddle.Width() >= rightBorder;
}
