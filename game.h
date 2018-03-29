#pragma once

#include <vector>
#include "vec2d.h"
#include "class_entity-brick.h"
#include "class_entity-edge.h"
#include "class_entity-paddle.h"
#include "allegrow.h"


class Game
{
public:
	Game(bool _game_is_running);
	~Game();
	void go();

	AllegroW allegrow;
	std::vector<Brick> bricks;
	std::vector<Edge> edges;
	Paddle paddle;
	bool game_is_running;
};
