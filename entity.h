#pragma once

#include "vector2d.h"
#include <allegro5\color.h>

struct Dimension
{
	Dimension() {}
	Dimension(float _w, float _h) : width(_w), height(_h) {}
	float left,
		  right,
		  top,
		  bot,
		  width,
		  height;
};

class Entity
{
public:
	Entity();
	Entity(Vector2D _coord, Dimension _dimension);
	~Entity();

	void set_sides();
	bool operator>(const Entity &_rhs) const;

	Vector2D coord;
	//Vector2D normal;
	Vector2D side;
	Dimension dimension;
	ALLEGRO_COLOR color;
	bool is_dead;
	float hp,
		  speed,
		  damage;

};
