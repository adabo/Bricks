//#include "game.h"
#include  <iostream>
#include "allegrow.h"
#include "game.h"

#define FPS 60

void sys_pause()
{
	std::cout << "Press Enter to continue ...";
	std::getchar();
}

//int main(int argc, int *argv[])
int main()
{
	Game game;
	AllegroW allegrow(game);

	allegrow.start_allgro_services();

	while (game.is_running) {
		allegrow.handle_events();
		allegrow.draw();
	}

	sys_pause();
	return 0;
}
