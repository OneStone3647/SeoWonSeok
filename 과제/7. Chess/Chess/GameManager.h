#pragma once
#include "BlockManager.h"
#include "BoardManager.h"
#include "Player.h"

// 턴을 관리하는 enum
enum TURN
{
	TURN_BLACK = 0,
	TURN_WHITE
};

class GameManager
{
private:
	Player*				m_PlayerBlack;
	Player*				m_PlayerWhite;
	bool				m_bFirstPlay;				// 첫 게임의 시작을 알린다.
	TURN				m_Turn;
	BoardManager*		m_BoardManager;


public:
	GameManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void DrawInitBoard();
	void Input(LPARAM lParam);
	void Inputt(LPARAM lParam);

	bool GetFirstFlag()
	{
		return m_bFirstPlay;
	}

	~GameManager();
};

