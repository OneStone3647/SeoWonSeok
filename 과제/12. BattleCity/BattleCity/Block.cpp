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
}

void Block::SetBlockType(BLOCKTYPE BlockType)
{
	m_BlockType = BlockType;
	if (m_BlockType == BLOCKTYPE_EMPTY)
	{
		m_Bitmap.Release();
		return;
	}
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
	SetBlockCollision(m_BlockType);
}

void Block::SetBlockCollision(BLOCKTYPE BlockType)
{
	switch (BlockType)
	{
	case BLOKCTYPE_BLOCK00:
	case BLOKCTYPE_BLOCK05:
	case BLOKCTYPE_BLOCK07:
	case BLOKCTYPE_BLOCK08:
	case BLOKCTYPE_BLOCK13:
		m_Collision.SetCollision(m_Point.x, m_Point.y);
		break;
	case BLOKCTYPE_BLOCK01:
	case BLOKCTYPE_BLOCK09:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_UP);
		break;
	case BLOKCTYPE_BLOCK02:
	case BLOKCTYPE_BLOCK10:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_LEFT);
		break;
	case BLOKCTYPE_BLOCK03:
	case BLOKCTYPE_BLOCK11:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_DOWN);
		break;
	case BLOKCTYPE_BLOCK04:
	case BLOKCTYPE_BLOCK12:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_RIGHT);
		break;
	case BLOKCTYPE_BLOCK06:
	case BLOCKTYPE_EMPTY:
		m_Collision.SetCollision(0, 0);
		break;
	}
}

void Block::Draw()
{
	m_Bitmap.Draw(m_MemDC, m_Point.x, m_Point.y, 2.0f);

}
