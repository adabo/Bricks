#include "game.h"

Game::Game(bool _game_is_running)
	:allegrow(_game_is_running)
{
	 AllegroW allegrow(game_is_running);
}

Game::~Game()
{

}

void Game::go()
{
	allegrow.start_allegro_services();

	while(!game_is_running) {

	}
}
