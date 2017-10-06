#include <assert.h>

#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Graphics& gfx, const Paddle& paddle, const std::vector<Rect>& walls) :
	gfx(gfx),
	paddle(paddle),
	walls(walls),
	velocity({ 0.0f, 0.0f }) {
	assert(walls.size() == 3);
}

void Ball::Update(float dt) {
	if (!paddle.BallLaunched()) {
		SetRelativeToPaddle();
		
		return;
	}

	HandleLaunch();
	HandleWallCollision();
	HandlePaddleCollision();

	topLeft += velocity * dt;
}

void Ball::Draw() const {
	SpriteCodex::DrawBall(Center(), gfx);
}

Vec2 Ball::Center() const {
	Vec2 center{ topLeft.x + Radius, topLeft.y + Radius };

	return center;
}

Rect Ball::GetRect() const {
	Rect rect = Rect(topLeft, topLeft.x + Radius * 2, topLeft.y + Radius * 2);

	return rect;
}

void Ball::SetRelativeToPaddle() {
	Vec2 paddleCenter = paddle.Center();
	topLeft.x = paddleCenter.x - Radius;
	topLeft.y = paddleCenter.y - paddle.GetHeight() - Radius;
}

void Ball::HandleLaunch() {
	if (paddle.BallLaunched() && !justLaunched) {
		justLaunched = true;
		velocity.y = -speed;
	}
}

void Ball::HandleWallCollision() {
	if (IsCollidingWithLeftWall() || IsCollidingWithRightWall()) {
		velocity.x = -velocity.x;
	}

	if (IsCollidingWithTopWall()) {
		velocity.y = -velocity.y;
	}
}

void Ball::HandlePaddleCollision() {
	if (!IsCollidingWithPaddle()) {
		return;
	}

	int paddleWidth = paddle.GetWidth();
	int paddleX = paddle.Center().x - paddleWidth / 2;
	int segmentSize = paddleWidth / PaddleXSegments;
	int paddleSegments[PaddleXSegments];

	for (size_t segment = 0; segment < PaddleXSegments; segment++)
	{
		paddleSegments[segment] = paddleX + segment * segmentSize;
	}

	int lastValueSegmentIndex = 6;
	int xValue = lastValueSegmentIndex;
	Vec2 center = Center();

	for (size_t i = 0; i < PaddleXSegments - 1; i++)
	{
		bool isInSector = (paddleSegments[i] <= center.x && center.x < paddleSegments[i + 1]);

		if (isInSector) {
			xValue = i;

			break;
		}
	}

	velocity.x = PaddleXTouchVelocityValues[xValue];
	velocity.y = -velocity.y;
}

bool Ball::IsCollidingWithLeftWall() const {
	return GetRect().IsCollidingWith(walls[0]);
}

bool Ball::IsCollidingWithTopWall() const {
	return GetRect().IsCollidingWith(walls[1]);
}

bool Ball::IsCollidingWithRightWall() const {
	return GetRect().IsCollidingWith(walls[2]);
}

bool Ball::IsCollidingWithPaddle() const {
	return GetRect().IsCollidingWith(paddle.GetRect());
}
