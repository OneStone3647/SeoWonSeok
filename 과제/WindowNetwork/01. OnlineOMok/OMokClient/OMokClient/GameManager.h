#pragma once
#include "Player.h"

class GameManager
{
private:
	Player*	m_Player;
	Player*	m_Enemy;

	int			m_Turn;
	bool		m_bTurnFlag;

	bool		m_bIsPlay;

public:
	GameManager();
	~GameManager();

public:
	void Init();
	void Reset();
	void Release();
	void Update();
	void Input();
	void EnemyUpdate();
	void DrawInfo(Player* player);
	void DrawAllStone();
	bool CheckStone(int x, int y);
	void DrawPlayer(Player* player);
	void ErasePlayer(Player* player);
	void DrawVictory(Player* player);
};

