#include "game.h"
#include <iostream>

Game::Game():game_is_running(true),line(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) {}

Game::~Game(){}

void Game::go()
{

	allegrow.start_allgro_services();

	allegrow.start_timer();

	while (game_is_running) {
		allegrow.handle_events(mouse, game_is_running);
		allegrow.update(line, mouse);
		allegrow.draw(line, mouse);
	}

	//sys_pause();
}
