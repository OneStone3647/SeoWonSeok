#include "Game.h"

int main()
{
	Game* game = new MyGame();

	game->Initialized();
	game->Update();
	game->Finished();

	delete game;
}