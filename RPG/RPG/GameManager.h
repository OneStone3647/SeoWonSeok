#pragma once
#include "Character.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	Character* Player;
	Character* Monster;

public:
	virtual void Initialized();
	virtual void Update();
	virtual void Finishied();

protected:
	virtual Character* CreateCharacter() = 0;
};

class Game : public GameManager
{
protected:
	virtual Character* CreateCharacter();
};

