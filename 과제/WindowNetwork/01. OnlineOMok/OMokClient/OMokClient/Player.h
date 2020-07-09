#pragma once
#include "Mecro.h"
#include "Stone.h"
#include <vector>

#define PUT 13
#define ESC 27

enum DIRECTION
{
	DIRECTION_UP = 'w',
	DIRECTION_LEFT = 'a',
	DIRECTION_DOWN = 's',
	DIRECTION_RIGHT = 'd'
};

class Player
{
private:
	int			m_Team;
	int			m_X;
	int			m_Y;
	bool		m_bIsMyTurn;

	vector<Stone*> m_Stone;
	string m_StoneShape;
	string m_PlayerName;

public:
	Player();
	~Player();

public:
	void Init();
	void Init(int team);
	void Release();
	void PutStone();
	bool SearchStone(int x, int y);
	int CheckNextStone(int x, int y, int addX, int addY);
	bool CheckVictory();

public:
	inline int GetX()
	{
		return m_X;
	}
	inline int GetY()
	{
		return m_Y;
	}
	inline void SetXY(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}
	inline void PlusX(int x)
	{
		m_X += x;
	}
	inline void PlusY(int y)
	{
		m_Y += y;
	}

	inline int GetTeam()
	{
		return m_Team;
	}

	inline string GetPlayerName()
	{
		return m_PlayerName;
	}

	inline vector<Stone*> GetAllStone()
	{
		return m_Stone;
	}

	inline string GetStoneShape()
	{
		return m_StoneShape;
	}

	inline int GetStoneSize()
	{
		return m_Stone.size();
	}
};

