#pragma once
#include "Bitmap.h"

// 블록의 종류
enum BLOCKTYPE
{
	BLOKCTYPE_BLOCK01 = 0,
	BLOCKTYPE_BLOCK02
};

class Block
{
private:
	HDC				m_MemDC;
	BLOCKTYPE		m_BlockType;
	Bitmap			m_Bitmap;
	POINT				m_Point;			// 블록의 좌표
	RECT				m_Rect;			// 블록의 선택 범위

public:
	Block();
	~Block();

public:
	void Init(HDC memDC, BLOCKTYPE blockType, int x, int y);
	void SetBlock(BLOCKTYPE blockType);

public:
	inline void Draw()
	{
		m_Bitmap.Draw(m_MemDC, m_Point.x, m_Point.y);
	}

	inline RECT GetRect()
	{
		return m_Rect;
	}
	inline void SetRect()
	{
		m_Rect = { BLOCKBIT_X * m_Point.x, BLOCKBIT_Y * m_Point.y, (BLOCKBIT_X * m_Point.x) + BLOCKBIT_Y, (BLOCKBIT_Y * m_Point.y) + BLOCKBIT_Y };
	}
};

