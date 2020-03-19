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

	m_bIsOpen = false;
	m_bIsFlag = false;
}

void MineBlock::Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY)
{
	Block::Init(MemDC, x, y, BlockStartX, BlockStartY);
	m_eBlock = BLOCK_MINE;
	m_MineBlock.Init(MemDC, "Bitmap\\mine.bmp");
}

void MineBlock::Draw()
{
	// 열었을 경우
	if (m_bIsOpen)
	{
		m_MineBlock.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
	}
	// 열지 않았을 경우
	else
	{
		// 깃발일 경우
		if (m_bIsFlag)
		{
			m_Flag.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
		}
		// 깃발이 아닌 경우
		else
		{
			m_Block.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
		}
	}
}

void SafeBlock::Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY)
{
	Block::Init(MemDC, x, y, BlockStartX, BlockStartY);
	m_eBlock = BLOCK_SAFE;
	m_MineCount = 0;
	NumberInit();
}

void SafeBlock::NumberInit()
{
	char buf[256];
	sprintf(buf, "Bitmap\\block_%d.bmp", m_MineCount);
	m_NumberBlock.Init(m_MemDC, buf);
}

void SafeBlock::Draw()
{
	// 열었을 경우
	if (m_bIsOpen)
	{
		m_NumberBlock.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
	}
	// 열지 않았을 경우
	else
	{
		// 깃발일 경우
		if (m_bIsFlag)
		{
			m_Flag.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
		}
		// 깃발이 아닌 경우
		else
		{
			m_Block.Draw(m_MemDC, m_StartPoint.x + BlockSize * m_Point.x, m_StartPoint.y + BlockSize * m_Point.y, BlockSize, BlockSize);
		}
	}
}
