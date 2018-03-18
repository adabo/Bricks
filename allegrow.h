#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\timer.h>
#include <allegro5\keyboard.h>
#include <allegro5\mouse.h>
#include <allegro5\allegro_font.h>
#include <vector>
//#include "vector2d.h"

#define FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//class Vector2D;
//class Game;

/* AllegroW: Allegrow Wrapper */
class Vector2D;
class Entity;

class AllegroW
{
public:
	AllegroW();
	~AllegroW();

	void start_allgro_services();

	void init_addons();
	void create_objects();
	void register_objects();
	void start_timer();
	void handle_events(Vector2D &_mouse, bool &_game_is_running);
	void handle_bullets_spawn(std::vector<Entity> &_bullet);
	void clamp_entity_to_screen(Vector2D &_entity_coord, int offset);
	void handle_collision(Entity &_ent1, Entity &_ent2);

	void draw(std::vector<Entity> &_bullet);
	void update(std::vector<Entity> &_bullets,
				std::vector<Entity> &_blocks,
				Entity &_paddle,
				Entity &_boundary);

	/* Temporary members*/
	float xt, yt;
	/********************/

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
