#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(HDC memDC, BLOCKTYPE blockType, int x, int y)
{
	m_MemDC = memDC;
	m_BlockType = blockType;
	m_Point.x = x;
	m_Point.y = y;
	SetRect();
	SetBlock(m_BlockType);
}

void Block::SetBlock(BLOCKTYPE blockType)
{
	switch (blockType)
	{
	case BLOKCTYPE_BLOCK01:
		m_Bitmap.Init(m_MemDC, "Bitmap\\block00.bmp");
		break;
	case BLOCKTYPE_BLOCK02:
		m_Bitmap.Init(m_MemDC, "Bitmap\\block01.bmp");
		break;
	}
}
