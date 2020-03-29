#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(HDC MemDC, int x, int y)
{
	m_MemDC = MemDC;

	m_BlockType = BLOCKTYPE_EMPTY;
	m_Point = { x, y };
	m_Collision.SetCollision(x, y);
}

void Block::SetBlockType(BLOCKTYPE BlockType)
{
	m_BlockType = BlockType;
	char buf[256];
	if (m_BlockType <= BLOKCTYPE_BLOCK09)
	{
		sprintf(buf, "Bitmap\\block0%d.bmp", m_BlockType);
	}
	else
	{
		sprintf(buf, "Bitmap\\block%d.bmp", m_BlockType);
	}
	m_Bitmap.Init(m_MemDC, buf);
}

void Block::Draw()
{
	if (m_BlockType != BLOCKTYPE_EMPTY)
	{
		m_Bitmap.Draw(m_MemDC, m_Point.x, m_Point.y, BlockSizeX, BlockSizeY);
	}
	else
	{
		HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);

		Rectangle(m_MemDC, m_Point.x, m_Point.y, m_Point.x + BlockSizeX, m_Point.y + BlockSizeY);

		SelectObject(m_MemDC, oldBrush);
	}
}
