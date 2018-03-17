#pragma once
#include <vector>
#include "entity.h"
#include "allegrow.h"
#include "vector2d.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

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
