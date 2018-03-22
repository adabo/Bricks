#include "game.h"

Game::Game()
	: game_is_running(true)
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
		allegrow.update(bullets, bricks, boundaries, paddle);
		allegrow.draw(bullets, bricks, boundaries, paddle);
	}

	//sys_pause();
}
