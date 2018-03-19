//#include <iostream>
#include "allegrow.h"
#include "vector2d.h"
#include "entity.h"
#include <iostream>
#include <stdio.h>

AllegroW::AllegroW()
	:	str(""),
		keystr(""),
		xt(1),
		yt(1),
		can_put_text(false),
		can_draw(false),
		can_update(false),
		key_is_down(false)
{}

AllegroW::~AllegroW() {}

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
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			x_mouse = event.mouse.x;
			y_mouse = event.mouse.y;
			mouse_button_is_down = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
				key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				_game_is_running = false;

			strcpy_s(keystr, al_keycode_to_name(event.keyboard.keycode));
			/* if the size of the typed characters (keystr) is less than 
			 * the size of the remainder string (array capacity - existing chars */
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

void AllegroW::draw(std::vector<Entity> &_bullets, std::vector<Entity> &_bricks, std::vector<Entity> &_boundaries)
{
	if (can_draw) {
		al_clear_to_color(al_map_rgb(0, 0 , 0));
		al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", "Testing");

		// Or draw_entity( Entity &_ent);
		draw_bullet(_bullets);
		draw_brick_grid(_bricks);
		draw_edge_boundaries(_boundaries);

		al_flip_display();
		can_draw = false;
	}
}

void AllegroW::draw_bullet(std::vector<Entity> &_bullets)
{
	// No need to continue if no bullets exist
	if (_bullets.size() > 0)
		for (int i = 0; i < _bullets.size(); ++i)
			al_draw_pixel(_bullets[i].coord.x, _bullets[i].coord.y,
				al_map_rgb(255, 0, 255));
}

void AllegroW::draw_brick_grid(std::vector<Entity> &_bricks)
{
	int i = 0;
	int col = 4, row = 8;
	float x,y,w,h;

	for (int c_index = 0; c_index < col; ++c_index) {
		for (int r_index = 0; r_index < row; ++r_index) {
			// Need to increment before skipping this iteration or else
			// the next loop will hold the previous index and do the same
			// thing over and over eg. all bricks appear dead and won't draw
			if (_bricks[i].is_dead) {++i; continue;}
			// temp assigment
			x = _bricks[i].coord.x,
			y = _bricks[i].coord.y,
		  	w = _bricks[i].dimension.width, 
	  		h = _bricks[i].dimension.height;

			al_draw_filled_rectangle(x, y, x + w, y + h,
									 al_map_rgb(100, 100, 100));
			++i;
		}
	}
}
void AllegroW::draw_edge_boundaries(std::vector<Entity> &_boundaries)
{
	int x,
		y,
		w,
		h = 0,
	    sides = 4;
		ALLEGRO_COLOR c;

	for (int i = 0; i < sides; ++i) {
		x = _boundaries[i].coord.x;
		y = _boundaries[i].coord.y;
		w = _boundaries[i].dimension.width;
		h = _boundaries[i].dimension.height;
		c = _boundaries[i].color; 
		al_draw_filled_rectangle(x,y,x+w,y+h,c);
	}
}
/* TODO Split updates per entity. Too many arguments for main update
 * But how do you pass ALL the entities from game? pass the whole game object?)
 * However, we could just load up the argument list with every single entity.
 * But how do you compare collision for EVERY entity against EVERY entity?*/
void AllegroW::update(std::vector<Entity> &_bullets,
					  std::vector<Entity> &_bricks,
					  std::vector<Entity> &_boundaries,
					  Entity &_paddle)
{
	if (can_update) {
		if (mouse_button_is_down) {
			spawn_entities(_bullets);
			spawn_edge_boundaries(_boundaries);
			mouse_button_is_down = false;
		}

		if (key_is_down) {
			spawn_brick_grid(_bricks);
			key_is_down = false;
		}

		// Increment heading
		if (_bullets.size() > 0) {
			for (int i = 0; i < _bullets.size(); ++i) {
				_bullets[i].coord.x += _bullets[i].coord.x_normal * _bullets[i].speed;
				_bullets[i].coord.y += _bullets[i].coord.y_normal * _bullets[i].speed;
			}

			// check if there's collision
			std::vector<Entity>::iterator brk_it = _bricks.begin();
			std::vector<Entity>::iterator blt_it = _bullets.begin();
			bool can_break = false;

			for (int blt = 0; blt < _bullets.size(); ++blt,++blt_it) {
				for (int brk = 0; brk < _bricks.size(); ++brk, ++brk_it) {
					// Always check entity dead so we don't recheck collision on it
					if (brk_it->is_dead) continue;

					if (is_colliding(_bullets[blt], _bricks[brk])) {
						// Set to true here and check for truth at draw time
						// ... for now?
						// TODO use remove_dead()
						brk_it->is_dead = true;
						blt_it->is_dead = true;

						_bullets.erase(blt_it);
						// No need to continue looping since we found the
						// entities that need to be removed/hp--
						can_break = true;
						break;
					}
				}
					
				if (can_break) break;
				// Reset bricks array iterator to first
				brk_it = _bricks.begin();
			}

			// Bounce bullet.
			// TODO Make each side of the screen an entity

		}

	}
	can_update = false;
}

void AllegroW::update_brick_grid(std::vector<Entity> &_bricks)
{

}

void AllegroW::spawn_entities(std::vector<Entity> &_bullets)
{
	// Add new bullet to end of array
	Vector2D new_coord(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 20);
	Dimension new_dimension(1,1);
	float speed = 7;
	_bullets.emplace_back(new_coord, new_dimension, speed);

  	//Get index # of last element
	int index = _bullets.size() - 1;

	// Set dimension of top,bot,left, right
	//_bullets[index].set_sides();

	// Normalize the vector
	float x = x_mouse;
	float y = y_mouse;
	_bullets[index].coord.normalize_length(x, y);
}

void AllegroW::clamp_entity_to_screen(Vector2D &_entity_coord, int offset)
{
	if      (_entity_coord.x < 1) 			  _entity_coord.x = 1;
	else if (_entity_coord.x > SCREEN_WIDTH)  _entity_coord.x = SCREEN_WIDTH - 1;
	else if (_entity_coord.y < 1) 			  _entity_coord.y = 1;
	else if (_entity_coord.y > SCREEN_HEIGHT) _entity_coord.y = SCREEN_HEIGHT -1;
}

bool AllegroW::is_colliding(Entity &_ent1, Entity &_ent2)
{
	_ent1.set_sides();
	_ent2.set_sides();
	return _ent1 > _ent2;
}

void AllegroW::spawn_brick_grid(std::vector<Entity> &_bricks)
{
	int col = 4, row = 8;

	_bricks.clear();

	for (int brick_count = 0; brick_count < col * row; ++brick_count) {
	}

	for (int c_index = 0; c_index < col; ++c_index) {
		for (int r_index = 0; r_index < row; ++r_index) {
			_bricks.emplace_back(Vector2D(r_index * 60, c_index * 60), Dimension(50,50),0);
			_bricks[_bricks.size() - 1].is_dead = false;
		}
	}
}

// I think this function can be reduced in size with a helper function
void AllegroW::spawn_edge_boundaries(std::vector<Entity> &_boundaries)
{
	_boundaries.clear();

	int index = 0;
	float x = 0,
		  y = 0,
		  w = SCREEN_WIDTH - 20,
		  h = 20;
	ALLEGRO_COLOR color = al_map_rgb(216, 61, 61); // Soft red
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h), 0); // Top
	_boundaries[index].color = color;
	++index;

	x = 20;
	y = SCREEN_HEIGHT - 20;
	w = SCREEN_WIDTH - 20;
	h = 20;
	color = al_map_rgb(100, 188, 100); // Soft green
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Bot
	_boundaries[index].color = color;
	++index;

	x = 0;
	y = 20;
	w = 20;
	h = SCREEN_HEIGHT - 20;
	color = al_map_rgb(66, 100, 190); // Soft blue
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Left
	_boundaries[index].color = color;
	++index;

	x = SCREEN_WIDTH - 20;
	y = 0;
	w = 20;
	h = SCREEN_HEIGHT - 20;
	color = al_map_rgb(180, 167, 75); // Soft 
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Right
	_boundaries[index].color = color;
}

void AllegroW::remove_dead(Entity &_entity)
{

}
void AllegroW::bounce_bullet()
{

}
