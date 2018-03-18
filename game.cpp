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

	allegrow.spawn_brick_grid(bricks);

	while (game_is_running) {
		allegrow.handle_events(paddle.coord, game_is_running);
		allegrow.update(bullets, bricks, paddle, boundary);
		allegrow.draw(bullets, bricks);
	}

	//sys_pause();
}
