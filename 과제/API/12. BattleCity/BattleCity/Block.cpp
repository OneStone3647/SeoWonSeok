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
	m_bIsWalkable = true;
	m_BrokeType = BROKETYPE_PASS;
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
	if (m_BlockType <= BLOCKTYPE_BLOCK09)
	{
		sprintf(buf, "Bitmap\\block0%d.bmp", m_BlockType);
	}
	else if (m_BlockType == BLOCKTYPE_BLOCK14)
	{
		sprintf(buf, "Bitmap\\block%d.bmp", m_BlockType - 1);
	}
	else
	{
		sprintf(buf, "Bitmap\\block%d.bmp", m_BlockType);
	}
	m_Bitmap.Init(m_MemDC, buf);
	SetBlockCollision();
	SetBlockInfo();
}

void Block::SetBlockCollision()
{
	switch (m_BlockType)
	{
	case BLOCKTYPE_BLOCK00:
	case BLOCKTYPE_BLOCK05:
	case BLOCKTYPE_BLOCK08:
	case BLOCKTYPE_BLOCK13:
	case BLOCKTYPE_BLOCK07:
		m_Collision.SetCollision(m_Point.x, m_Point.y);
		break;
	case BLOCKTYPE_BLOCK01:
	case BLOCKTYPE_BLOCK09:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_UP);
		break;
	case BLOCKTYPE_BLOCK02:
	case BLOCKTYPE_BLOCK10:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_LEFT);
		break;
	case BLOCKTYPE_BLOCK03:
	case BLOCKTYPE_BLOCK11:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_DOWN);
		break;
	case BLOCKTYPE_BLOCK04:
	case BLOCKTYPE_BLOCK12:
		m_Collision.SetCollision(m_Point.x, m_Point.y, COLLISIONTYPE_RIGHT);
		break;
	case BLOCKTYPE_BLOCK06:
	case BLOCKTYPE_BLOCK14:
	case BLOCKTYPE_EMPTY:
		m_Collision.SetCollision(0, 0);
		break;
	}
}

void Block::SetBlockInfo()
{
	switch (m_BlockType)
	{
	case BLOCKTYPE_BLOCK00:
	case BLOCKTYPE_BLOCK01:
	case BLOCKTYPE_BLOCK02:
	case BLOCKTYPE_BLOCK03:
	case BLOCKTYPE_BLOCK04:
	case BLOCKTYPE_BLOCK13:
		m_bIsWalkable = false;
		m_BrokeType = BROKETYPE_ABLE;
		break;
	case BLOCKTYPE_BLOCK05:
	case BLOCKTYPE_BLOCK08:
	case BLOCKTYPE_BLOCK09:
	case BLOCKTYPE_BLOCK10:
	case BLOCKTYPE_BLOCK11:
	case BLOCKTYPE_BLOCK12:
		m_bIsWalkable = false;
		m_BrokeType = BROKETYPE_UNABLE;
		break;
	case BLOCKTYPE_BLOCK07:
		m_bIsWalkable = false;
		m_BrokeType = BROKETYPE_PASS;
		break;
	case BLOCKTYPE_BLOCK06:
		m_bIsWalkable = true;
		m_BrokeType = BROKETYPE_PASS;
		break;
	case BLOCKTYPE_BLOCK14:
	case BLOCKTYPE_EMPTY:
		m_bIsWalkable = true;
		m_BrokeType = BROKETYPE_PASS;
		break;
	}
}

void Block::Draw()
{
	m_Bitmap.Draw(m_MemDC, m_Point.x, m_Point.y, 2.0f);
}
