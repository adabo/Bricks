#include "game.h"

Game::Game()
	: game_is_running(true), allegrow(game_is_running)
{
}

Game::~Game(){}

void Game::go()
{

	allegrow.start_allgro_services();

	allegrow.start_timer();

	allegrow.spawn_paddle(paddle);

	allegrow.spawn_brick_grid(bricks);

	allegrow.spawn_edge_boundaries(boundaries);

	while (game_is_running) {
		allegrow.handle_events(paddle.coord, game_is_running);
		allegrow.update(balls, bricks, boundaries, paddle);
		allegrow.draw(balls, bricks, boundaries, paddle);
	}

	//sys_pause();
}
