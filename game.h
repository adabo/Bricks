#pragma once
#include <vector>

class Vector2D;
class Entity;

class Game
{
public:
	Game();
	~Game();

	bool is_running;
	std::vector<Entity> bullet;
	Entity hero,
		   block,
		   paddle,
		   boundary;
};
