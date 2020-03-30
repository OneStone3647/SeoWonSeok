#pragma once
#include "Bitmap.h"
#include "Collision.h"

enum BLOCKTYPE
{
	BLOKCTYPE_BLOCK00,
	BLOKCTYPE_BLOCK01,
	BLOKCTYPE_BLOCK02,
	BLOKCTYPE_BLOCK03,
	BLOKCTYPE_BLOCK04,
	BLOKCTYPE_BLOCK05,
	BLOKCTYPE_BLOCK06,
	BLOKCTYPE_BLOCK07,
	BLOKCTYPE_BLOCK08,
	BLOKCTYPE_BLOCK09,
	BLOKCTYPE_BLOCK10,
	BLOKCTYPE_BLOCK11,
	BLOKCTYPE_BLOCK12,
	BLOKCTYPE_BLOCK13,
	BLOKCTYPE_BLOCK14,
	BLOCKTYPE_EMPTY
};

class Block
{
private:
	HDC				m_MemDC;

	BLOCKTYPE		m_BlockType;
	Bitmap			m_Bitmap;
	POINT				m_Point;
	Collision			m_Collision;

public:
	Block();
	~Block();

public:
	void Init(HDC MemDC, int x, int y);
	void SetBlockType(BLOCKTYPE BlockType);
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
};

