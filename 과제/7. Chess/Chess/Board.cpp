#include "Board.h"



Board::Board()
{
	m_BoardInfo = BOARDINFO_NONE;
}

void Board::Init(int x, int y)
{
	m_Rect = { BLOCKX * x, BLOCKY * y, (BLOCKX * x) + BLOCKX, (BLOCKY * y) + BLOCKY };
}


Board::~Board()
{
}
