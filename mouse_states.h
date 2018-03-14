#pragma once

//#include <allegro5/allegro.h>
union ALLEGRO_EVENT;

struct MouseStates
{
	void save_mouse_action(ALLEGRO_EVENT &_event);
	bool button_is_down;
	int x, y;
};

