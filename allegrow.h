#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\timer.h>
#include <allegro5\keyboard.h>
#include <allegro5\mouse.h>
#include <allegro5\allegro_font.h>
#include "vec2d.h"
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60

class AllegroW
{
public:
	AllegroW(bool &_game_is_running);
	~AllegroW();
	void start_allegro_services();
	void init_addons();
	void create_objects();
	void register_objects();
	void start_timer();
	void handle_events(Vec2D &_mouse, bool &_game_is_running);

	float x_mouse, y_mouse;
	bool can_draw;
	bool can_update;
	bool enter_key_is_down;
	bool left_key_is_down;
   	bool right_key_is_down;
	bool a_key_is_down;
   	bool d_key_is_down;
	bool w_key_is_down;
	bool backspace_key_is_down;
	bool space_key_is_down;
	bool mouse_button_is_down;
	bool &game_is_running;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
};
