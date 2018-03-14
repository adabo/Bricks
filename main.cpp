#include "game.h"
#include  <iostream>

void sys_pause()
{
	std::cout << "Press Enter to continue ...";
	std::getchar();
}

int main(int argc, int *argv[])
{
	sys_pause();
	return 0;
}