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
	void spawn_entities(std::vector<Entity> &_bullets);
	void clamp_entity_to_screen(Vector2D &_entity_coord, int offset);
	void draw(std::vector<Entity> &_bullets, std::vector<Entity> &_bricks);
	void draw_bullet(std::vector<Entity> &_bullets);
	void draw_brick_grid(std::vector<Entity> &_bricks);
	void update(std::vector<Entity> &_bullets,
				std::vector<Entity> &_bricks,
				Entity &_paddle,
				Entity &_boundary);
	void update_brick_grid(std::vector<Entity> &_bricks);
	bool is_colliding(Entity &_ent1, Entity &_ent2);
	void spawn_brick_grid(std::vector<Entity> &_bricks);
	void remove_dead(Entity &_entity);

	/* Temporary members*/
	float xt, yt;
	/********************/

	float x_mouse, y_mouse;
	char keystr[10];
	char str[40];
	bool can_put_text;
	bool can_draw;
	bool can_update;
	bool mouse_button_is_down;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font;
};
