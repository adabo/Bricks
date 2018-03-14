#include "game.h"

int main(int argc, char *argv[])
{
	Game game;
	//Game update; // TODO what was I thinking here??
	AllegroW allegro(game);
	allegro.init_framework();
	// Game loop
	while (game.is_running) {
		allegro.init_timeout();
		allegro.handle_events();
		game.update();
		game.draw();
	}

	allegro.cleanup();

	return allegro.exit_code;
}
