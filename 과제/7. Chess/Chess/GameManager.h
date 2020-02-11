#pragma once
#include "BlockManager.h"
#include "Board.h"
#include "Player.h"

// ���� �����ϴ� enum
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
	bool					m_bFirstPlay;				// ù ������ ������ �˸���.
	TURN					m_Turn;
	Board**				m_Board;


public:
	GameManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBoardInit();
	void SetBoardInPieceInit(Player* player);
	void DrawInitBoard();
	void Input(LPARAM lParam);

	bool GetFirstFlag()
	{
		return m_bFirstPlay;
	}

	~GameManager();
};

