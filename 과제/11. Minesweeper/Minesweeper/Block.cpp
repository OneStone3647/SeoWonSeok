#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

void Block::Init(HDC MemDC)
{
	m_MemDC = MemDC;

	m_Block[BLOCKINDEX_BLANK].Init(m_MemDC, "Bitmap\\block.bmp");
	m_Block[BLOCKINDEX_0].Init(m_MemDC, "Bitmap\\block_0.bmp");
	m_Block[BLOCKINDEX_1].Init(m_MemDC, "Bitmap\\block_1.bmp");
	m_Block[BLOCKINDEX_2].Init(m_MemDC, "Bitmap\\block_2.bmp");
	m_Block[BLOCKINDEX_3].Init(m_MemDC, "Bitmap\\block_3.bmp");
	m_Block[BLOCKINDEX_4].Init(m_MemDC, "Bitmap\\block_4.bmp");
	m_Block[BLOCKINDEX_5].Init(m_MemDC, "Bitmap\\block_5.bmp");
	m_Block[BLOCKINDEX_6].Init(m_MemDC, "Bitmap\\block_6.bmp");
	m_Block[BLOCKINDEX_7].Init(m_MemDC, "Bitmap\\block_7.bmp");
	m_Block[BLOCKINDEX_8].Init(m_MemDC, "Bitmap\\block_8.bmp");
	m_Block[BLOCKINDEX_FLAG].Init(m_MemDC, "Bitmap\\flag.bmp");
	m_Block[BLOCKINDEX_MINE].Init(m_MemDC, "Bitmap\\mine.bmp");
}
