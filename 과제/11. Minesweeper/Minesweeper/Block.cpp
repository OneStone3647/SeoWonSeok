#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY)
{
	m_MemDC = MemDC;

	m_Block.Init(m_MemDC, "Bitmap\\block.bmp");
	m_Flag.Init(m_MemDC, "Bitmap\\flag.bmp");

	m_Point = { x, y };
	m_StartPoint = { BlockStartX, BlockStartY };
	m_Collision = { BlockStartX + BlockSize * x, BlockStartY + BlockSize * y,
		BlockStartX + BlockSize * (x + 1), BlockStartY + BlockSize * (y + 1) };

	m_bIsFlag = false;
}
