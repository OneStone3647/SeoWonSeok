#pragma once
#include "Player.h"

enum TURN
{
	TURN_BLACK = 0,
	TURN_WHITE
};

class GameManager
{
private:
	Player* m_PlayerBlack;
	Player* m_PlayerWhite;
	bool m_bFirstPlay;
	TURN m_Turn;

public:
	GameManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void Input(LPARAM lParam);
	bool CheckWinner(Player* player);
	void Release();

	bool GetFirstPlayFlag()
	{
		return m_bFirstPlay;
	}
	void SetFirstplayFlag(bool bFlag)
	{
		m_bFirstPlay = bFlag;
	}
	~GameManager();

public:
	inline Player* GetPlayerBlack()
	{
		return m_PlayerBlack;
	}
	inline Player* GetPlayerWhite()
	{
		return m_PlayerWhite;
	}
};

