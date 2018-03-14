#pragma once

//#include <allegro5/allegro.h>
//#include <allegro5/keyboard.h>

union ALLEGRO_EVENT;
struct KeyStates
{
public:
	void save_key_state(ALLEGRO_EVENT &_event);

	ALLEGRO_EVENT &event;
	bool w_is_down;
	bool s_is_down;
	bool a_is_down;
	bool d_is_down;
	bool esc_is_down;
};

