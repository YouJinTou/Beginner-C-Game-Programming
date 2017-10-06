#pragma once

#include "Graphics.h"
#include "Mouse.h"
#include "Vec2.h"

class Dude
{
public:
	void ClampToScreen();
	void Draw( Graphics& gfx ) const;
	void Update( const Mouse& ms,float dt );
	Vec2 GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
private:
	Vec2 pos = Vec2( 400.0f,300.0f );
	Vec2 dest;
	static constexpr float speed = 1.0f * 60.0f;
	static constexpr float width = 20.0f;
	static constexpr float height = 20.0f;
};