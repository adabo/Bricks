#include "mouse_states.h"

void MouseStates::save_mouse_action(ALLEGRO_EVENT &_event)
{
	switch(_event.type) {
		case ALLEGRO_EVENT_MOUSE_AXES:
			x = _event.mouse.x;
			y = _event.mouse.y;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			button_is_down = true;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			button_is_down = false;
			break;
		default: break;
	}
}
