#pragma once
#include "Block.h"

class BlockManager
{
private:
	HDC								m_MemDC;

	int									m_MapX;
	int									m_MapY;
	int									m_BlockStartX;
	int									m_BlockStartY;

	vector<vector<Block*>>		m_Block;

public:
	BlockManager();
	~BlockManager();

public:
	void Init(HDC MemDC, int MapSizeX, int MapSizeY, int BlockStartX, int BlockStartY);
	void DrawAllBlock();
};

