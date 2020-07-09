#pragma once
#include "Bitmap.h"

// ����� ����
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
	POINT				m_Point;			// ����� ��ǥ
	RECT				m_Rect;			// ����� ���� ����

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

