#include <iostream>
#include "game.h"
#include "allegrow.h"


AllegroW::AllegroW(Game &_game)
	:	str(""),
		xt(1),
		yt(1),
		can_put_text(false),
		can_draw(false),
		can_update(false),
		game(_game)
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
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
}

void AllegroW::start_timer()
{
	al_start_timer(timer);
}

void AllegroW::handle_events()
{
	al_wait_for_event(event_queue, &event);

	switch (event.type) {
	case ALLEGRO_EVENT_KEY_DOWN:
		if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			game.is_running = false;
		strcat_s(str, al_keycode_to_name(event.keyboard.keycode));
		break;
	case ALLEGRO_EVENT_TIMER:
		if (al_is_event_queue_empty(event_queue)) {
			can_put_text = true;
			can_draw = true;
			can_update = true;
		}
		break;
	default:
		break;
	}
}

void AllegroW::draw()
{
	if (can_put_text) {
		al_clear_to_color(al_map_rgb(0, 0 , 0));
		al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", str);
		al_flip_display();
		can_put_text = false;
	}
	if (can_draw) {
		al_draw_pixel(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					  al_map_rgb(255, 0, 255));
		can_draw = false;
	}
}

void AllegroW::update(){}