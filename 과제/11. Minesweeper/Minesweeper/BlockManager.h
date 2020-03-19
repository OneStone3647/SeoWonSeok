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

	int									m_MineCount;

public:
	BlockManager();
	~BlockManager();

public:
	void Init(HDC MemDC, int MapSizeX, int MapSizeY, int BlockStartX, int BlockStartY, int MineCount);
	void Release();
	void SetMine();
	void DrawAllBlock();
	void CheckBlock(MOUSECLICK PlayerClick, POINT MousePoint);
};

