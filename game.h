#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

class Game
{
public:
	Game();
	~Game();
	void init_allegro_systems();
	void init_allegro();
	void init_addons();
	void init_timer();
	void init_display();
	void create_event_queue();
	void register_event_sources();
	void display_screen();
	void start_timer();
	void init_timeout();
	void handle_events();
	void update();
	void draw();
	void cleanup();

	bool is_running;
	bool can_redraw;
	int return_value;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
};
