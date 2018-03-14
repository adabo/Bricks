#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::update()
{
	player.update();
	bullet.update();
	entity.update();
}

void Game::draw()
{
	player.draw();
	bullet.draw();
	entity.draw();
}
