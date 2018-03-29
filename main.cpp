#include "game.h"

int main(int argc, char *argv[])
{
	Game game(false);

	game.go();

	std::getchar();
	return 0;
}
