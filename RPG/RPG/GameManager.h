#pragma once
#include "CharacterFactory.h"

enum SELECT
{
	SELECT_SCISSORS = 49,
	SELECT_ROCK,
	SELECT_PAPER
};

class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	Character* m_Player;
	Character* m_NPC;

public:
	void Init();
	void Update();
	void Finish();
	Character* SetPlayer();
	Character* SetNPC();
	char SelectNPC();
	bool CheckWinner(Character* player, Character* npc);
};

