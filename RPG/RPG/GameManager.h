#pragma once
#include "CharacterFactory.h"

enum SELECTCHARACTER
{
	SELECTCHARACTER_PLAYER = 1,
	SELECTCHARACTER_NPC
};

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	Character* Player;
	Character* NPC;

public:
	virtual void Initialized();
	virtual void Update();
	virtual void Finishied();

protected:
	virtual Character* CreateCharater(SELECTCHARACTER select) = 0;
};

class Game : public GameManager
{
protected:
	virtual Character* CreateCharater(SELECTCHARACTER select);
};

