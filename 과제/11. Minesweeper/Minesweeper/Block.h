#pragma once
#include "Bitmap.h"

enum BLOCKINDEX
{
	BLOCKINDEX_BLANK,
	BLOCKINDEX_0,
	BLOCKINDEX_1,
	BLOCKINDEX_2,
	BLOCKINDEX_3,
	BLOCKINDEX_4,
	BLOCKINDEX_5,
	BLOCKINDEX_6,
	BLOCKINDEX_7,
	BLOCKINDEX_8,
	BLOCKINDEX_FLAG,
	BLOCKINDEX_MINE
};

class Block
{
private:
	HDC			m_MemDC;

	Bitmap		m_Block[12];
	int				m_BlockIndex;

public:
	Block();
	~Block();

public:
	void Init(HDC MemDC);

public:
	inline void DrawBlock(int BlockIndex, int x, int y, int SizeX, int SizeY)
	{
		m_Block[BlockIndex].Draw(m_MemDC, x, y, SizeX, SizeY);
	}
};

