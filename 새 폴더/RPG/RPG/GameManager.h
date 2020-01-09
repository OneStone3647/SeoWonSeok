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
	Character* m_Player;
	Character* m_NPC;
	Creator* m_Creator;

public:
	void Initialized();
	void Update();
	void Finishied();
};

// 팩토리 매서드
class Creator : public GameManager
{
public:
	Character* CreateCharater(SELECTCHARACTER select);
};

