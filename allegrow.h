/* AllegroW: Allegro Wrapper */
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

class Vector2D;
class Entity;

class AllegroW
{
public:
	AllegroW(bool &_game_is_running);
	AllegroW();
	~AllegroW();

	void start_allgro_services();

	void init_addons();
	void create_objects();
	void register_objects();
	void start_timer();
	void handle_events(Vector2D &_mouse, bool &_game_is_running);
	void clamp_entity_to_screen(Vector2D &_entity_coord, int offset);
	void draw(std::vector<Entity> &_balls,
			  std::vector<Entity> &_bricks,
			  std::vector<Entity> &_boundaries,
			  Entity &_paddle);
	void draw_paddle(Entity &_paddle);
	void draw_ball(std::vector<Entity> &_balls);
	void draw_brick_grid(std::vector<Entity> &_bricks);
	void draw_edge_boundaries(std::vector<Entity> &_boundaries);
	void draw_win();
	void draw_lose();
	void update(std::vector<Entity> &_balls,
				std::vector<Entity> &_bricks,
				std::vector<Entity> &_boundaries,
				Entity &_paddle);
	void handle_ball_collision(std::vector<Entity> &_balls,
							   std::vector<Entity> &_edges,
							   bool _is_edge);
	void handle_ball_collision(std::vector<Entity> &_balls,
								Entity &_paddle,
								bool _is_edge);
	bool is_colliding(Entity &_ent1, Entity &_ent2);
	void spawn_paddle(Entity &_paddle);
	void spawn_entities(std::vector<Entity> &_balls);
	void spawn_brick_grid(std::vector<Entity> &_bricks);
	void spawn_edge_boundaries(std::vector<Entity> &_boundaries);
	void remove_dead(Entity &_entity);
	void bounce_ball(Entity &_ball);
	bool player_did_win(std::vector<Entity> &_bricks);
	bool player_did_lose(std::vector<Entity> &_edges);
	void check_victory_conditions(std::vector<Entity> &_bricks,
								  std::vector<Entity> &_edges);

	/* Temporary members*/
	float xt, yt;
	/********************/

	float x_mouse, y_mouse;
	char keystr[10];
	char str[40];
	bool can_put_text;
	bool can_draw;
	bool can_update;
	bool can_show_win_screen;
	bool can_show_lose_screen;
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
