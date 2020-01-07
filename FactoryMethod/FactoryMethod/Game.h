#pragma once
#include "View.h"

class Game
{
private:
	View* view;

public:
	Game();
	~Game();

public:
	virtual void Initialized();
	virtual void Update();
	virtual void Finished();
	
protected:
	virtual View* CreateView() = 0;
};

class MyGame : public Game
{
protected:
	virtual View* CreateView();
};

