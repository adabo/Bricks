#pragma once
#include <vector>
#include "entity.h"
#include "allegrow.h"
#include "vector2d.h"

class Game
{
public:
	Game();
	~Game();
	
	void go();

	AllegroW allegrow;

	Vector2D mouse;
	bool game_is_running;
	std::vector<Entity> bullet;
	Vector2D line;
	Entity hero,
		   block,
		   paddle,
		   boundary;
};
