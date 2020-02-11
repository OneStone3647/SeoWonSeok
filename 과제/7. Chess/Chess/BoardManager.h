#pragma once
#include "Board.h"
#include "Player.h"

class BoardManager
{
private:
	Board**	m_Board;

public:
	BoardManager();

	void Init();
	void SetBoardInPieceInit(Player* player);
	void MovePieceInBoard(POINT beforePoint, POINT afterPoint, BOARDINFO boardInfo);
	bool CheckMoveInBoard(POINT currentPoint, POINT goalPoint);

	~BoardManager();

public:
	inline Board** GetBoard()
	{
		return m_Board;
	}
};

