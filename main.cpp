#include  <iostream>
#include "allegrow.h"
#include "game.h"

#define FPS 60

void sys_pause()
{
	std::cout << "Press Enter to continue ..." << std::endl;
	std::getchar();
}

int main(int argc, int *argv[])
{
	Game game;
	game.go();
	return 0;
}
