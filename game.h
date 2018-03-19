#pragma once
//#include <vector>
#include "entity.h"
#include "allegrow.h"
//#include "vector2d.h"

class Vector2D;

class Game
{
public:
	Game();
	~Game();
	
	void go();

	AllegroW allegrow;

	//Vector2D mouse;
	//Vector2D line;
	bool game_is_running;
	std::vector<Entity> bullets;
	std::vector<Entity> bricks;
	std::vector<Entity> boundaries;
	Entity paddle;
};
