//#include <iostream>
#include "allegrow.h"
#include "vector2d.h"
#include "entity.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

AllegroW::AllegroW()
	:	str(""),
		keystr(""),
		xt(1),
		yt(1),
		can_put_text(false),
		can_draw(false),
		can_update(false),
		enter_key_is_down(false)
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
			x_mouse = event.mouse.x;
			y_mouse = event.mouse.y;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			x_mouse = event.mouse.x;
			y_mouse = event.mouse.y;
			mouse_button_is_down = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
				enter_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
				left_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_W)
				w_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_D)
				d_key_is_down = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				space_key_is_down = true;
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
		case ALLEGRO_EVENT_KEY_UP:
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
				left_key_is_down = false;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right_key_is_down = false;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				space_key_is_down = false;
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

void AllegroW::draw(std::vector<Entity> &_balls,
					std::vector<Entity> &_bricks,
					std::vector<Entity> &_boundaries,
					Entity &_paddle)
{
	if (can_draw) {
		al_clear_to_color(al_map_rgb(0, 0 , 0));
		al_draw_textf(font, al_map_rgb(0, 255, 0), xt, yt, 0, "%s", "Testing");

		// Or draw_entity( Entity &_ent);
		draw_paddle(_paddle);
		draw_ball(_balls);
		draw_brick_grid(_bricks);
		draw_edge_boundaries(_boundaries);

		al_flip_display();
		can_draw = false;
	}
}

void AllegroW::draw_ball(std::vector<Entity> &_balls)
{
	// No need to continue if no balls exist
	if (_balls.size() > 0)
		for (float i = 0; i < _balls.size(); ++i)
			al_draw_filled_circle(_balls[i].coord.x + 4,
								  _balls[i].coord.y + 4,
								  4, al_map_rgb(255, 0, 255));
			//al_draw_pixel(_balls[i].coord.x, _balls[i].coord.y,
				//al_map_rgb(255, 0, 255));
}

void AllegroW::draw_brick_grid(std::vector<Entity> &_bricks)
{
	float x,y,
		  w = _bricks[0].dimension.width,
		  h = _bricks[0].dimension.height;

	for (float i = 0; i < _bricks.size(); ++i) {
		if (_bricks[i].is_dead) continue;

			// temp assigment
			x = _bricks[i].coord.x;
			y = _bricks[i].coord.y;

			al_draw_filled_rectangle(x, y, x + w, y + h,
									 al_map_rgb(100, 100, 100));
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

	for (float i = 0; i < sides; ++i) {
		x = _boundaries[i].coord.x;
		y = _boundaries[i].coord.y;
		w = _boundaries[i].dimension.width;
		h = _boundaries[i].dimension.height;
		c = _boundaries[i].color; 
		//al_draw_filled_rectangle(x,y,x+w,y+h,c);
		al_draw_rectangle(x,y,x+w,y+h,c, 1);
	}
}

void AllegroW::draw_paddle(Entity &_paddle)
{
	int x = _paddle.coord.x,
		y = _paddle.coord.y,
		w = _paddle.dimension.width, 
		h = _paddle.dimension.height;

	al_draw_filled_rectangle(x, y, x + w, y + h,
							 al_map_rgb(100, 100, 100));
}
/* TODO Split updates per entity. Too many arguments for main update
 * But how do you pass ALL the entities from game? pass the whole game object?)
 * However, we could just load up the argument list with every single entity.
 * But how do you compare collision for EVERY entity against EVERY entity?*/
void AllegroW::update(std::vector<Entity> &_balls,
					  std::vector<Entity> &_bricks,
					  std::vector<Entity> &_boundaries,
					  Entity &_paddle)
{
	if (can_update) {
		if (mouse_button_is_down || space_key_is_down) {
			spawn_entities(_balls);
			mouse_button_is_down = false;
			space_key_is_down = false;
		}

		if (enter_key_is_down) {
			spawn_brick_grid(_bricks);
			enter_key_is_down = false;
		}

		// Move paddle
		// by mouse
		//_paddle.coord.x = x_mouse - _paddle.dimension.width / 2;
		//_paddle.coord.y = y_mouse - _paddle.dimension.height / 2;
		
		// Move paddle
		// by keyboard
		if (left_key_is_down || w_key_is_down) {
			_paddle.coord.x -= _paddle.speed; 
		}
		else if (right_key_is_down || d_key_is_down) {
			_paddle.coord.x += _paddle.speed; 
		}

		// Increment heading
		if (_balls.size() > 0) {
			for (float i = 0; i < _balls.size(); ++i) {
				_balls[i].coord.x += _balls[i].coord.x_normal * _balls[i].speed;
				_balls[i].coord.y += _balls[i].coord.y_normal * _balls[i].speed;
			}

			// check if there's collision
			// First destroy the brick
			//handle_ball_brick_collision(_balls, _bricks);
			// then bounce off brick
			bool is_edge = false;
			handle_ball_collision(_balls, _bricks, is_edge);

			is_edge = false;
			handle_ball_collision(_balls, _paddle, is_edge);
			// then check and bounce on screen edges.
			is_edge = true;
			handle_ball_collision(_balls, _boundaries, is_edge);


			// Bounce ball.
			// TODO Make each side of the screen an entity

		}

	}
	can_update = false;
}

void AllegroW::update_brick_grid(std::vector<Entity> &_bricks)
{

}

void AllegroW::handle_ball_brick_collision(std::vector<Entity> &_balls,
											 std::vector<Entity> &_bricks)
{
	std::vector<Entity>::iterator blt_it = _balls.begin();
	std::vector<Entity>::iterator brk_it = _bricks.begin();

	bool can_break = false;


	for (float blt = 0; blt < _balls.size(); ++blt,++blt_it) {
		for (float brk = 0; brk < _bricks.size(); ++brk, ++brk_it) {
			// Always check entity dead so we don't recheck collision on it
			if (brk_it->is_dead) continue;

			if (is_colliding(_balls[blt], _bricks[brk])) {
				std::cout << "Collision" << std::endl;
				// Set to true here and check for truth at draw time
				// ... for now?
				// TODO use remove_dead()
				brk_it->is_dead = true;
				blt_it->is_dead = true;

				//_balls.erase(blt_it);
				//bounce_ball(_balls[blt]);

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
}

// Helper for checking which edge is being hit
// TODO please move enum somewhere better
enum SIDE { TOP, BOT, LEFT, RIGHT, NONE };
float get_bisect(Vector2D &_destination, Vector2D &_origin)
{
	// This returns the normalized length of the base of the triangle
	// value between 0.0 -> 0.99...
	Vector2D bisect = _origin;
	bisect.normalize_length(_destination.x, _destination.y);

	return abs(bisect.x_normal);
}

SIDE check_top_right(Entity &_ent1, Entity &_ent2)
{
	// Get vector (B) between vec1 lower left point and vec2 top right point.
	// Then compare vec1.y_normal length to the vectorB.y_normal. If it is less
	// then the collision happened on the top. Else the right.
	Vector2D entity1_bot_left(_ent1.coord.x, _ent1.coord.y + _ent1.dimension.height);
	Vector2D entity2_top_right(_ent2.coord.x + _ent2.dimension.width, _ent2.coord.y);

	if (abs(_ent1.coord.x_normal) < get_bisect(entity2_top_right, entity1_bot_left))
		return TOP;
	else
		return RIGHT;
}

SIDE check_bot_left(Entity &_ent1, Entity &_ent2)
{
	Vector2D entity1_top_right(_ent1.coord.x + _ent1.dimension.width, _ent1.coord.y);
	Vector2D entity2_bot_left(_ent2.coord.x, _ent2.coord.y + _ent2.dimension.height);

	if (abs(_ent1.coord.x_normal) < get_bisect(entity2_bot_left, entity1_top_right))
		return BOT;
	else
		return LEFT;
}

SIDE check_top_left(Entity &_ent1, Entity &_ent2)
{
	Vector2D entity1_bot_right(_ent1.coord.x + _ent1.dimension.width,
							   _ent1.coord.y + _ent1.dimension.height);
	Vector2D entity2_top_left(_ent2.coord.x, _ent2.coord.y + _ent2.dimension.height);

	if (abs(_ent1.coord.x_normal) < get_bisect(entity2_top_left, entity1_bot_right))
		return TOP;
	else
		return LEFT;
}

SIDE check_bot_right(Entity &_ent1, Entity &_ent2)
{
	Vector2D entity1_top_left(_ent1.coord.x, _ent1.coord.y);
	Vector2D entity2_bot_right(_ent2.coord.x + _ent2.dimension.width,
							   _ent2.coord.y + _ent2.dimension.height);

	if (abs(_ent1.coord.x_normal) < get_bisect(entity2_bot_right, entity1_top_left))
		return BOT;
	else
		return RIGHT;
}

SIDE get_which_side(Entity &_ent1, Entity &_ent2)
{
	// Going down-left
	if (_ent1.coord.y_normal > 0 && _ent1.coord.x_normal <= 0) // Down-left
		return check_top_right(_ent1, _ent2);
	// Going up-right
	else if (_ent1.coord.y_normal < 0 && _ent1.coord.x_normal >= 0) // Up-right
		return check_bot_left(_ent1, _ent2);
	// Going down-right
	else if (_ent1.coord.y_normal > 0 && _ent1.coord.x_normal >= 0) // Down-right
		return check_top_left(_ent1, _ent2);
	// Going up-left
	else if (_ent1.coord.y_normal < 0 && _ent1.coord.x_normal <= 0) // Up-left
		return check_bot_right(_ent1, _ent2);
	else
		return NONE;
}


float get_sin(float &_cos)
{
	float sin = 0;
	float hyp = 1;
	sin = sqrt(hyp * hyp - _cos * _cos);
	return sin;
}

void AllegroW::handle_ball_collision(std::vector<Entity> &_balls,
									   Entity &_paddle,
									   bool _is_edge)
{
	std::vector<Entity>::iterator it_bal = _balls.begin();

	for (float bal = 0; bal < _balls.size(); ++it_bal, ++bal) {
		if (is_colliding(_balls[bal], _paddle)) {
			if (!_is_edge) {
				_paddle.is_dead = true;
				_balls[bal].is_dead = true;
			}
			SIDE side = get_which_side(_balls[bal], _paddle);
			float paddle_half_width = _paddle.dimension.width / 2;
			switch (side) {
			case TOP:
				// To make the paddle collision like arkanoid, the x axis
				// needs to be altered slightly depending on the position the
				// ball collides with the paddle.
				if (_balls[bal].coord.x < _paddle.coord.x + paddle_half_width) {
					float distance = _paddle.coord.x - _balls[bal].coord.x;
					float half_pos = paddle_half_width + distance;
					float new_heading = half_pos / paddle_half_width;

					_balls[bal].coord.x_normal = -new_heading;
					_balls[bal].coord.y_normal = -get_sin(new_heading);
				}
				else if (_balls[bal].coord.x > _paddle.coord.x + paddle_half_width) {
					float distance = (_paddle.coord.x + _paddle.dimension.width) -
									 (_balls[bal].coord.x + _balls[bal].dimension.width);
					float half_pos = paddle_half_width - abs(distance);
					float new_heading = half_pos / paddle_half_width;

					_balls[bal].coord.x_normal = new_heading;
					_balls[bal].coord.y_normal = -get_sin(new_heading);
				}

				//_balls[bal].coord.y_normal = -_balls[bal].coord.y_normal;
				// Move ball back outside of the object it collided with because a collision
				// means that some part of the ball is *inside* of the object. This formula
				// puts the ball back outside of the object so that it does infinitely loop
				// stuck insdie of the object.
				_balls[bal].coord.y -= (_balls[bal].coord.y + _balls[bal].dimension.height) - _paddle.coord.y;
				break;
			case RIGHT:
				_balls[bal].coord.x_normal = -_balls[bal].coord.x_normal;
				_balls[bal].coord.x -= _balls[bal].coord.x - (_paddle.coord.x + _paddle.dimension.width);
				break;
			case BOT:
				_balls[bal].coord.y_normal = -_balls[bal].coord.y_normal;
				_balls[bal].coord.y -= _balls[bal].coord.y - (_paddle.coord.y + _paddle.dimension.height);
				break;
			case LEFT:
				_balls[bal].coord.x_normal = -_balls[bal].coord.x_normal;
				_balls[bal].coord.x -= (_balls[bal].coord.x + _balls[bal].dimension.width) - _paddle.coord.x;
				break;
			default:
				break;
			}
		}
	}
}

void AllegroW::handle_ball_collision(std::vector<Entity> &_balls,
									   std::vector<Entity> &_entity,
									   bool _is_edge)
{
	std::vector<Entity>::iterator it_bal = _balls.begin();
	std::vector<Entity>::iterator it_ent = _entity.begin();

	for (float bal = 0; bal < _balls.size(); ++it_bal, ++bal) {
		bool can_break = false;
		for (float ent = 0; ent < _entity.size(); ++it_ent, ++ent) {
			if (_entity[ent].is_dead) continue;

			if (is_colliding(_balls[bal], _entity[ent])) {
				if (!_is_edge) {
					_entity[ent].is_dead = true;
					_balls[bal].is_dead = true;
				}

				SIDE side = get_which_side(_balls[bal], _entity[ent]);

				switch (side) {
					case TOP:
						_balls[bal].coord.y_normal = -_balls[bal].coord.y_normal;
						_balls[bal].coord.y -= (_balls[bal].coord.y + _balls[bal].dimension.height) - _entity[ent].coord.y;
						can_break = true;
						break;
					case RIGHT:
						_balls[bal].coord.x_normal = -_balls[bal].coord.x_normal;
						_balls[bal].coord.x -= _balls[bal].coord.x - (_entity[ent].coord.x + _entity[ent].dimension.width);
						can_break = true;
						break;
					case BOT:
						// Reverse ball travel vector (heading)
						_balls[bal].coord.y_normal = -_balls[bal].coord.y_normal;
						// Move ball out of colliding object
						_balls[bal].coord.y -= _balls[bal].coord.y - (_entity[ent].coord.y + _entity[ent].dimension.height);
						can_break = true;
						break;
					case LEFT:
						_balls[bal].coord.x_normal = -_balls[bal].coord.x_normal;
						_balls[bal].coord.x -= (_balls[bal].coord.x + _balls[bal].dimension.width) - _entity[ent].coord.x;
						can_break = true;
						break;
					default:
						break;
				}
			}
			if (can_break) break;
		}
		can_break = false;
		// The entity iterator must be reset because it will remember the last
		// position when the for loop starts over. The outer for loop remembers
		// because it never *breaks*
		it_ent = _entity.begin();
	}
}

void AllegroW::spawn_paddle(Entity &_paddle)
{
	Vector2D new_coord(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 50);
	Dimension new_dimension(100, 20);

	//_paddle(Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50), Dimension(100, 20), 4);
	_paddle = { new_coord, new_dimension, 4 };
}

void AllegroW::spawn_entities(std::vector<Entity> &_balls)
{
	// Add new ball to end of array
	Vector2D new_coord(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 60);
	Dimension new_dimension(8,8);
	float speed = 5;
	_balls.emplace_back(new_coord, new_dimension, speed);

  	//Get index # of last element
	int index = _balls.size() - 1;

	// Set dimension of top,bot,left, right
	//_balls[index].set_sides();

	// Normalize the vector
	float x = x_mouse;
	float y = y_mouse;
	_balls[index].coord.normalize_length(x, y);
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
	// Erase all array elements
	_bricks.clear();

	// Grid always stretches across screen with 4 pixels between
	// each brick and 8 bricks wide
	// 40 is 20 * 2 for 20 pixel wide screen edge left and right
	// row - 1 is the number of gaps between the 8 bricks (or whatever amount)
	float col = 8, row = 4,
	      brick_gap = 4,
	      edge_offset = 20,
		  w = (SCREEN_WIDTH - ((edge_offset * 2) + ((brick_gap * col) - 1))) / col,
	      h = 20,
	      x = edge_offset,
		  y = edge_offset;

	int i = 0;
	for (float r_index = 0; r_index < row; ++r_index) {
		for (float c_index = 0; c_index < col; ++c_index, ++i) {
			// Set brick coords, width & height
			_bricks.emplace_back(Vector2D(x,y), Dimension(w,h),0);

			// Set default dead to false
			_bricks[i].is_dead = false;

			// Increment x&y coordinate by accordingly
			x += w + brick_gap;
		}
		y += h + brick_gap;
		x = edge_offset;
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
	_boundaries[index].is_dead = false;
	++index;

	x = 20;
	y = SCREEN_HEIGHT - 20;
	w = SCREEN_WIDTH - 20;
	h = 20;
	color = al_map_rgb(100, 188, 100); // Soft green
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Bot
	_boundaries[index].color = color;
	_boundaries[index].is_dead = false;
	++index;

	x = 0;
	y = 20;
	w = 20;
	h = SCREEN_HEIGHT - 20;
	color = al_map_rgb(66, 100, 190); // Soft blue
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Left
	_boundaries[index].color = color;
	_boundaries[index].is_dead = false;
	++index;

	x = SCREEN_WIDTH - 20;
	y = 0;
	w = 20;
	h = SCREEN_HEIGHT - 20;
	color = al_map_rgb(180, 167, 75); // Soft 
	_boundaries.emplace_back(Vector2D(x,y), Dimension(w, h),0); // Right
	_boundaries[index].color = color;
	_boundaries[index].is_dead = false;
}

void AllegroW::remove_dead(Entity &_entity)
{

}

void AllegroW::bounce_ball(Entity &_ball)
{
	if (_ball.coord.x > SCREEN_WIDTH - 6 || _ball.coord.x < 6)
		_ball.coord.x_normal = -_ball.coord.x_normal;
	if (_ball.coord.y > SCREEN_HEIGHT - 6 || _ball.coord.y < 6)
		_ball.coord.y_normal = -_ball.coord.y_normal;
}
