#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\timer.h>
#include <allegro5\keyboard.h>
#include <allegro5\allegro_font.h>
#include "vector2d.h"

#define FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game;

/* AllegroW: Allegrow Wrapper */
class AllegroW
{
public:
	AllegroW(Game &_game);
	~AllegroW();

	void start_allgro_services();

	void init_addons();
	void create_objects();
	void register_objects();
	void start_timer();
	void handle_events();

	void draw();
	void update();

	/* Temporary members*/
	float xt, yt;
	/********************/

	Vector2D line;
	Game &game;
	char keystr[10];
	char str[40];
	bool can_put_text;
	bool can_draw;
	bool can_update;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
};
