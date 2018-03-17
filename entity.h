#pragma once
#include "vector2d.h"

#include <allegro5\color.h>

class Entity
{
public:
	Entity();
	~Entity();

	Vector2D coord;
	Vector2D normal;
	Vector2D side;

	ALLEGRO_COLOR color;
	float hp,
		  speed,
		  damage;

};
