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

	while (game_is_running) {
		allegrow.handle_events(paddle.coord, game_is_running);
		allegrow.update(bullets, blocks, paddle, boundary);
		allegrow.draw(bullets);
	}

	//sys_pause();
}
