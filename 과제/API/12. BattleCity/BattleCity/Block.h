#pragma once
#include "Bitmap.h"
#include "Collision.h"

enum BLOCKTYPE
{
	BLOCKTYPE_BLOCK00,
	BLOCKTYPE_BLOCK01,
	BLOCKTYPE_BLOCK02,
	BLOCKTYPE_BLOCK03,
	BLOCKTYPE_BLOCK04,
	BLOCKTYPE_BLOCK05,
	BLOCKTYPE_BLOCK06,
	BLOCKTYPE_BLOCK07,
	BLOCKTYPE_BLOCK08,
	BLOCKTYPE_BLOCK09,
	BLOCKTYPE_BLOCK10,
	BLOCKTYPE_BLOCK11,
	BLOCKTYPE_BLOCK12,
	BLOCKTYPE_BLOCK13,
	BLOCKTYPE_EMPTY,
	BLOCKTYPE_BLOCK14
};

enum BROKETYPE
{
	BROKETYPE_ABLE,
	BROKETYPE_UNABLE,
	BROKETYPE_PASS
};

class Block
{
private:
	HDC				m_MemDC;

	BLOCKTYPE		m_BlockType;
	Bitmap			m_Bitmap;
	POINT				m_Point;
	Collision			m_Collision;
	bool				m_bIsWalkable;
	BROKETYPE		m_BrokeType;

public:
	Block();
	~Block();

public:
	void Init(HDC MemDC, int x, int y);
	void SetBlockType(BLOCKTYPE BlockType);
	void SetBlockCollision();
	void SetBlockInfo();
	void Draw();

public:
	inline BLOCKTYPE GetBlockType()
	{
		return m_BlockType;
	}

	inline POINT GetBlockPoint()
	{
		return m_Point;
	}

	inline Collision GetCollision()
	{
		return m_Collision;
	}
	inline void SetCollision(int x, int y)
	{
		m_Collision.SetCollision(x, y);
	}

	inline bool GetWalkable()
	{
		return m_bIsWalkable;
	}

	inline BROKETYPE GetBrokeType()
	{
		return m_BrokeType;
	}
};

