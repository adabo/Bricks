#include "allegrow.h"
#include <iostream>
AllegroW::AllegroW(bool &_game_is_running)
	: game_is_running(_game_is_running),
	  can_draw(false),
	  can_update(false),
	  a_key_is_down(false),
	  d_key_is_down(false),
	  w_key_is_down(false),
	  backspace_key_is_down(false),
	  space_key_is_down(false),
	  enter_key_is_down(false),
	  mouse_button_is_down(false)
{

}

AllegroW::~AllegroW()
{

}

void AllegroW::start_allegro_services()
{
	std::cout << "Starting allegro services ..." << std::endl;
	init_addons();
	create_objects();
	register_objects();
}

void AllegroW::init_addons()
{
	std::cout << "Initializing addons ..." << std::endl;
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_primitives_addon();
}

void AllegroW::create_objects()
{
	std::cout << "Creating objects ..." << std::endl;
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	font = al_create_builtin_font();
}

void AllegroW::register_objects()
{
	std::cout << "Registering objects ..." << std::endl;
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
}

void AllegroW::start_timer()
{
	std::cout << "Starting timer ..." << std::endl;
	al_start_timer(timer);
}

void AllegroW::handle_events(Vec2D &_mouse, bool &_game_is_running)
{
	std::cout << "Handling events ..." << std::endl;
	al_wait_for_event(event_queue, &event);
	int num_chars = 0;
	int num_limit = 0;

	switch (event.type) {
		case ALLEGRO_EVENT_MOUSE_AXES:
			x_mouse = event.mouse.x;
			y_mouse = event.mouse.y;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			x_mouse = event.mouse.x;
			y_mouse = event.mouse.y;
			mouse_button_is_down = true;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			mouse_button_is_down = false;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
				enter_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				left_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_W)
				w_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_A)
				a_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_D)
				d_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				space_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				backspace_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				_game_is_running = false;

			//strcpy_s(keystr, al_keycode_to_name(event.keyboard.keycode));
			///* if the size of the typed characters (keystr) is less than 
			// * the size of the remainder string (array capacity - existing chars */
			//num_chars = strlen(keystr);
			//num_limit = sizeof(str) - strlen(str);
			//if (num_chars < num_limit) strcat_s(str, keystr);
			/* then append/concatenate the characters to the end of str*/
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				left_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_A)
				a_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_D)
				d_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_W)
				w_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				backspace_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				space_key_is_down = false;
			break;
		case ALLEGRO_EVENT_TIMER:
			if (al_is_event_queue_empty(event_queue)) {
				can_update = true;
				can_draw = true;
			}
			break;
		default:
			break;
	}
}

