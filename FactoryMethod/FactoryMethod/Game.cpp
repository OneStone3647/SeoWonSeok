#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::Initialized()
{
	view = CreateView();
}

void Game::Update()
{
	view->Render();
}

void Game::Finished()
{
	delete view;
}

View* MyGame::CreateView()
{
	return new MyView();
}
