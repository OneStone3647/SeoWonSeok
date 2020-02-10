#pragma once
#include "BlockManager.h"
#include "Player.h"

// 턴을 관리하는 enum
enum TURN
{
	TURN_BLACK = 0,
	TURN_WHITE
};

// 보드에 존재하는 말의 종류를 설정하는 enum
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
	bool			m_bFirstPlay;		// 첫 게임의 시작을 알린다.
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

