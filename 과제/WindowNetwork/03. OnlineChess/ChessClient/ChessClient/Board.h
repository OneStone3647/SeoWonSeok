#pragma once
#include "Block.h"

class Board
{
private:
	vector<vector<Block*>>		m_Board;
	int									m_BoardX;
	int									m_BoardY;
public:
	Board();
	~Board();

public:
	void Init(HDC MemDC);
	void Release();
	void InitBoard(HDC MemDC);
	void DrawBoard();
};

