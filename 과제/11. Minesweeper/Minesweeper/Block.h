#pragma once
#include "Bitmap.h"

enum BLOCK
{
	BLOCK_SAFE,
	BLOCK_MINE
};

class Block
{
private:
	HDC			m_MemDC;
	Bitmap		m_Block;
	Bitmap		m_Flag;

	BLOCK		m_eBlock;

	POINT			m_Point;
	POINT			m_StartPoint;
	RECT			m_Collision;

	bool			m_bIsFlag;

public:
	Block();
	~Block();

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);

public:
	inline void DrawBlock()
	{
		m_Block.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
	}
	inline void DrawFlag(int SizeX = BlockSize, int SizeY = BlockSize)
	{
		m_Flag.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
	}
};

class Mine : public Block
{

};

class Safe : public Block
{

};

