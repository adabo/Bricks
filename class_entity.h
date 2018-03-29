#pragma once

#include "vec2d.h"

class Entity
{
public:
	enum SIDE {TOP, BOT, LEFT, RIGHT}side;
	struct Dimension {float w,h,top,bot,left,right;}dimension;

	Entity(Vec2D _coords);
	Entity();

	virtual void update_coords() = 0;
	virtual void update_dimensions() = 0;
	virtual void update_colliding() = 0;
	virtual void draw() = 0;

	Vec2D coords;
};
