//#include <iostream>
#include "allegrow.h"
#include "vector2d.h"
#include <stdio.h>

AllegroW::AllegroW()
	:	str(""),
		keystr(""),
		xt(1),
		yt(1),
		can_put_text(false),
		can_draw(false),
		can_update(false)
{}

AllegroW::~AllegroW(){}

void AllegroW::start_allgro_services()
{
	init_addons();
	create_objects();
	register_objects();
}

void AllegroW::init_addons()
{
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_primitives_addon();
}

void AllegroW::create_objects()
{
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	font = al_create_builtin_font();
}

void AllegroW::register_objects()
{
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
}

void AllegroW::start_timer()
{
	al_start_timer(timer);
}

void AllegroW::handle_events(Vector2D &_mouse, bool &_game_is_running)
{
	al_wait_for_event(event_queue, &event);
	int num_chars = 0;
	int num_limit = 0;

	switch (event.type) {
		case ALLEGRO_EVENT_MOUSE_AXES:
			_mouse.x = event.mouse.x;
			_mouse.y = event.mouse.y;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				_game_is_running = false;

			strcpy_s(keystr, al_keycode_to_name(event.keyboard.keycode));
			/* if the size of the typed characters is less than 
			 * the size of the remainder string */
			num_chars = strlen(keystr);
			num_limit = sizeof(str) - strlen(str);
			if (num_chars < num_limit) strcat_s(str, keystr);
			/* then append/concatenate the characters to the end of str*/
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

void AllegroW::draw(Vector2D &_line, Vector2D &_mouse)
{
	if (can_draw) {
		al_clear_to_color(al_map_rgb(0, 0 , 0));

		//al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", str);
		char result[50];
		sprintf_s(result, "%f", _mouse.x);
		al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", result);

		// Draw line
		for (int i = 0; i < 40; ++i) {
			_line.x += _line.x_normal;
			_line.y += _line.y_normal;
			al_draw_pixel(_line.x, _line.y,
					  al_map_rgb(255, 0, 255));
		}

		_line.x = SCREEN_WIDTH / 2;
		_line.y = SCREEN_HEIGHT / 2;

		al_flip_display();
		can_draw = false;
	}
}

void AllegroW::update(Vector2D &_line, Vector2D &_mouse)
{
	if (can_update)
		_line.normalize_length(_mouse.x, _mouse.y);
	can_update = false;
}
