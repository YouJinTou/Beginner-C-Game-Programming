#include "Paddle.h"

Paddle::Paddle(Graphics& gfx, int leftBorder, int rightBorder) :
	gfx(gfx), 
	leftBorder(leftBorder),
	rightBorder(rightBorder) {
	startX = (gfx.ScreenWidth / 2) - Width / 2;
	startY = gfx.ScreenHeight - Height;
	topLeft = Vec2(startX, startY);
}

void Paddle::Update(const std::string& command, const float dt) {
	if (command == "left") {
		topLeft.x = IsCollidingWithLeftWall() ? leftBorder : topLeft.x - (dt * Speed);
	}
	else if (command == "right") {
		topLeft.x = IsCollidingWithRightWall() ? rightBorder - Width : topLeft.x + (dt * Speed);
	}
	else if (command == "launch") {
		ballLaunched = true;
	}
}

void Paddle::Draw() const {
	Rect rect = GetRect();

	gfx.DrawRect(rect, wingsColor);
	gfx.DrawRect(
		rect.X() + WingsLength, 
		rect.Y() + WingsLength, 
		rect.Width() - WingsLength, 
		rect.Height() - WingsLength, 
		paddleColor);
}

Rect Paddle::GetRect() const {
	Rect rect{ topLeft, topLeft.x + Width, topLeft.y + Height };

	return rect;
}

Vec2 Paddle::Center() const
{
	Vec2 center{topLeft.x + Width / 2, topLeft.y + Height / 2};

	return center;
}

int Paddle::GetWidth() const
{
	return Width;
}

int Paddle::GetHeight() const
{
	return Height;
}

bool Paddle::BallLaunched() const
{
	return ballLaunched;
}

void Paddle::Reset() {
	ballLaunched = false;
	topLeft = Vec2(startX, startY);
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
