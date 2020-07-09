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
	int									m_FlagCount;
	int									m_OpenCount;			// 지뢰가 아닌 블록이 열린 개수

	bool								m_DrawAll;

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
	void Update(MOUSECLICK PlayerClick, POINT MousePoint, bool* bGameStart, bool* bGameOver);
	void OpenBlock(int x, int y);

public:
	inline vector<vector<Block*>> GetBlock()
	{
		return m_Block;
	}

	inline int GetFlagCount()
	{
		return m_FlagCount;
	}

	inline int GetOpenCount()
	{
		return m_OpenCount;
	}

	inline bool GetDrawAll()
	{
		return m_DrawAll;
	}
	inline void SetDrawAll()
	{
		m_DrawAll = false;
	}
};

