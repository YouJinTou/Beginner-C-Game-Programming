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
	velocity = { 0, 0 };
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
	Rect rect = GetRect();
	std::vector<Rect> walls = this->walls;

	if (IsCollidingWithLeftWall()) {
		topLeft.x += walls[0].Width() - rect.X();
		velocity.x = -velocity.x;
	}
	else if (IsCollidingWithRightWall()) {
		topLeft.x -= rect.Width() - walls[2].X();
		velocity.x = -velocity.x;
	}

	if (IsCollidingWithTopWall()) {
		topLeft.y += walls[1].Height() - rect.Y();
		velocity.y = -velocity.y;
	}
}

void Ball::HandlePaddleCollision() {
	if (!IsCollidingWithPaddle()) {
		return;
	}

	onHitPaddle.Play();

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
	Vec2 center = Center();
	float ballX = ball.X();
	float ballY = ball.Y();
	float ballX2 = ball.Width();
	float ballY2 = ball.Height();
	float bestDist = 99999.0f;
	Brick* bestBrick = nullptr;
	bool collisionExists = false;

	for (Brick& brick : bricks) {
		Rect brect = brick.GetRect();

		if (brick.isDestroyed || !ball.IsCollidingWith(brect)) {
			continue;
		}

		collisionExists = true;
		float dist = (brect.Center() - ball.Center()).GetLengthSq();

		if (dist < bestDist) {
			bestDist = dist;
			bestBrick = &brick;
		}
	}

	if (collisionExists) {
		DoBrickCollision(bestBrick);
	}
}

void Ball::DoBrickCollision(Brick* brick) {
	Rect brect = brick->GetRect();
	Vec2 center = Center();
	bool isLeft = center.x <= brect.X();
	bool isTop = center.y <= brect.Y();
	bool isRight = center.x >= brect.Width();
	bool isBot = center.y >= brect.Height();
	brick->isDestroyed = true;

	if (isBot || isTop) {
		velocity.y = -velocity.y;
	}
	else if (isLeft || isRight) {
		velocity.x = -velocity.x;
	}

	onHitBrick.Play();
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
