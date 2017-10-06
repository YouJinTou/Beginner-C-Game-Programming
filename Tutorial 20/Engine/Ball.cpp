#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Graphics & gfx, Paddle & paddle) :
	gfx(gfx),
	paddle(paddle) {
	Vec2 paddleCenter = paddle.Center();
}

void Ball::Update() {
	if (!paddle.BallLaunched()) {
		SetRelativeToPaddle();
	}
	else {

	}
}

void Ball::Draw() const {
	SpriteCodex::DrawBall(topLeft, gfx);
}

Vec2 Ball::Center() const {
	Vec2 center{ topLeft.x + Radius, topLeft.y + Radius };

	return center;
}

void Ball::SetRelativeToPaddle() {
	Vec2 paddleCenter = paddle.Center();
	topLeft.x = paddleCenter.x;
	topLeft.y = paddleCenter.y - paddle.GetHeight();
}
