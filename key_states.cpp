#include "key_states.h"
#include <allegro5\allegro.h>

void KeyStates::save_key_state(ALLEGRO_EVENT &_event)
{
	if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W: w_is_down = true; break;
			case ALLEGRO_KEY_S: s_is_down = true; break;
			case ALLEGRO_KEY_A: a_is_down = true; break;
			case ALLEGRO_KEY_D: d_is_down = true; break;
			case ALLEGRO_KEY_ESCAPE: esc_is_down = true; break;
			default: break;
		}
	}
	if (event.type == ALLEGRO_EVENT_KEY_UP) {
		switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_W: w_is_down = false; break;
			case ALLEGRO_KEY_S: s_is_down = false; break;
			case ALLEGRO_KEY_A: a_is_down = false; break;
			case ALLEGRO_KEY_D: d_is_down = false; break;
			case ALLEGRO_KEY_ESCAPE: esc_is_down = false; break;
			default: break;
		}
	}
}

