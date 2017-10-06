#include <assert.h>

#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Graphics& gfx, 
	const Paddle& paddle, 
	const std::vector<Rect>& walls,
	std::vector<Brick>& bricks) :
	gfx(gfx),
	paddle(paddle),
	walls(walls),
	bricks(bricks),
	velocity({ 0.0f, 0.0f }) {
	assert(walls.size() == 3);
}

void Ball::Update(float dt) {
	if (!paddle.BallLaunched()) {
		SetRelativeToPaddle();
		
		return;
	}

	if (IsLost()) {
		return;
	}

	HandleLaunch();
	HandleWallCollision();
	HandlePaddleCollision();
	HandleBrickCollision();

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
	justLaunched = false;
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

void Ball::HandleBrickCollision() {
	Rect ball = GetRect();
	float ballX = ball.X();
	float ballY = ball.Y();
	float ballX2 = ball.Width();
	float ballY2 = ball.Height();

	for (Brick& brick : bricks) {
		Rect brect = brick.GetRect();

		if (brick.isDestroyed || !ball.IsCollidingWith(brect)) {
			continue;
		}

		brick.isDestroyed = true;
		bool isLeft = ballX <= brect.Width();
		bool isTop = ballY <= brect.Height();
		bool isRight = ballX2 >= brect.X();
		bool isBot = ballY2 >= brect.Y();

		if (isBot || isTop) {
			velocity.y = -velocity.y;
		} 
		else if (isLeft || isRight) {
			velocity.x = -velocity.x;
		}
	}
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

bool Ball::IsLost() const {
	Rect rect = GetRect();
	int y = rect.Y() + (rect.Height() - rect.Y());

	return y >= gfx.ScreenHeight;
}
