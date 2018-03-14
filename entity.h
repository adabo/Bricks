#pragma once

#include "vector2D.h"
#include "coordinate.h"

class Entity
{
public:
	Entity();
	~Entity();
	void update();
	void draw();

	bool is_dead;
	Coordinate coord;
};
