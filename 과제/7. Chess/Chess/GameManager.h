#pragma once
#include "BlockManager.h"
#include "Player.h"

// ���� �����ϴ� enum
enum TURN
{
	TURN_BLACK = 0,
	TURN_WHITE
};

// ���忡 �����ϴ� ���� ������ �����ϴ� enum
enum BOARD
{
	BOARD_NONE = 0,
	BOARD_BLACK,
	BOARD_WHITE
};

class GameManager
{
private:
	BlockManager*	m_BlockManager;
	Player*			m_PlayerBlack;
	Player*			m_PlayerWhite;
	bool			m_bFirstPlay;		// ù ������ ������ �˸���.
	TURN			m_Turn;
	BOARD**			m_Board;


public:
	GameManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBoardInit();
	void SetBoardInPieceInit(Player* player);
	void DrawInitBoard();

	~GameManager();
};

