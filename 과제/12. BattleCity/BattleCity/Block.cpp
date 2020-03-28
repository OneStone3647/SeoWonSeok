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
	m_Collision.SetCollision(x, y);
}

void Block::SetBlockType(BLOCKTYPE BlockType)
{
	char buf[256];
	sprintf(buf, "Bitmap\\block_%d.bmp", BlockType);
	m_NumberBlock.Init(m_MemDC, buf);
	m_Bitmap.Init(m_MemDC, "Bitmap")
}
