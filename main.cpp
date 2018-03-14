#include "game.h"
#include  <iostream>

void sys_pause()
{
	std::cout << "Press Enter to continue ...";
	std::getchar();
}

int main(int argc, int *argv[])
{
	Game game;
	game.init_allegro_systems();

	while (game.is_running){
		game.init_timeout();
		game.handle_events();
		game.update();
		game.draw();
	}

	sys_pause();
	return 0;
}
