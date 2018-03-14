#pragma once

#include "allegro_wrapper.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <iostream>
//#include "game.h"
#include "mouse_states.h"
#include "key_states.h"

#define FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game;

class AllegroW
{
public: 
	AllegroW(Game &_game);
	AllegroW();
	~AllegroW();
	void init_framework();
	void init_allegro();
	void init_timer();
	void start_timer();
	void init_display();
	void init_addons();
	void create_event_queue();
	void register_event_sources();
	void init_timeout();
	void handle_events();
	void cleanup();

	ALLEGRO_KEYBOARD_STATE current_state;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMEOUT timeout;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	Game &game;
	MouseStates mouse;
	KeyStates kbd;
	bool can_update;
	bool can_redraw;
	int exit_code;
};
