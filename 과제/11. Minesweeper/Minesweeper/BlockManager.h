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
	void CheckMine(int x, int y);
	void SetMine();
	void SetNumberBlock();
	void DrawAllBlock();
	void OpenBlock(MOUSECLICK PlayerClick, POINT MousePoint, bool* bGameOver);
	void OpenBlock(int x, int y);

public:
	inline vector<vector<Block*>> GetBlock()
	{
		return m_Block;
	}
};

