#pragma once

#include <iostream>
#include <vector>
#include "allegro_wrapper.h"
#include "entity.h"
#include "key_states.h"
#include "mouse_states.h"
#include "vector2D.h"
#include "update.h"
#include "draw.h"


class Game
{
public:
	Game();
	~Game();

	void update();
	void draw();

	bool is_running;
	bool can_update;
	bool can_redraw;

	AllegroW allegro;
	KeyStates keybd;
	MouseStates mouse;
	Entity player;
	Entity bullet;
	Entity enemy;
};

