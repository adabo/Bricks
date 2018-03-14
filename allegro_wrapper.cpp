#include "allegro_wrapper.h"
#include "game.h"

AllegroW::AllegroW(Game &_game) : game(_game) {}

AllegroW::AllegroW()
{
}

AllegroW::~AllegroW() {}

void AllegroW::init_framework()
{
	init_allegro();
	init_timer();
	start_timer();
	init_display();
	init_addons();
	create_event_queue();
	register_event_sources();
	init_timeout();
	handle_events();
}

void AllegroW::init_allegro()
{
	if (!al_init()) {
		std::cout << stderr << " Failed to initialize allegro.\n";
		exit_code =  1;
	}
	else std::cout << stderr << " al_init success.\n";
}
void AllegroW::init_timer()
{
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		std::cout << stderr << " Failed to create timer.\n";
		exit_code =  1;
	}
	else std::cout << stderr << " al_create_timer success.\n";
}

void AllegroW::start_timer()
{
	al_start_timer(timer);
}

void AllegroW::init_display()
{
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		std::cout << stderr << " Failed to create display.\n";
		exit_code = 1;
	}
	else std::cout << stderr << " al_create_display success.\n";
}

void AllegroW::init_addons()
{
	if (!al_init_primitives_addon()){
		std::cout << stderr << " Failed to initialize primitives addon.\n";
		exit_code =  1;
	}
	else std::cout << stderr << " al_init_primitives_addon Success.";

	if (!al_install_keyboard()) {
		std::cout << stderr << " Failed to install keyboard.\n";
		exit_code =  1;
	}
	else std::cout << stderr << " al_install_keyboard() Success.";

	if (!al_install_mouse()) {
		std::cout << stderr << " Failed to install mouse.\n";
		exit_code =  1;
	}
	else std::cout << stderr << " al_install_mouse() Success.";
}

void AllegroW::create_event_queue()
{
	event_queue = al_create_event_queue();
	if (!event_queue) {
		std::cout << stderr << " Failed to create event queue.";
		exit_code = 1;
	}
	else std::cout << stderr << "al_create_event_queue success.\n";
}

void AllegroW::register_event_sources()
{
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
}

void AllegroW::init_timeout()
{
	al_init_timeout(&timeout, 0.06);
}

void AllegroW::handle_events()
{
	// Fetch the event (if one exists)
	al_wait_for_event(event_queue, &event);

	switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			// Check if the queue is empty before any updates or draw calls
			if (al_is_event_queue_empty(event_queue)) {
				can_update = true;
				can_redraw = true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE: game.is_running = false; break;
		case ALLEGRO_EVENT_KEY_DOWN: kbd.save_key_state(event); break;
		case ALLEGRO_EVENT_KEY_UP: kbd.save_key_state(event); break;
		case ALLEGRO_EVENT_MOUSE_AXES: mouse.save_mouse_action(event); break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: mouse.save_mouse_action(event); break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP: mouse.save_mouse_action(event); break;
		default: break;
	}
}

void AllegroW::cleanup()
{
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
}
