#define OLC_PGE_APPLICATION
#include "game.h"

int main()
{
	Game game;
	if (game.Construct(800, 800, 1, 1))
		game.Start();
	return 0;
}