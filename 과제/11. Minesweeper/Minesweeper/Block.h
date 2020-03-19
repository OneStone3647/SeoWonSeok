#pragma once
#include "Bitmap.h"

enum BLOCK
{
	BLOCK_SAFE,
	BLOCK_MINE
};

class Block
{
protected:
	HDC			m_MemDC;
	Bitmap		m_Block;
	Bitmap		m_Flag;

	BLOCK		m_eBlock;

	POINT			m_Point;
	POINT			m_StartPoint;
	RECT			m_Collision;

	bool			m_bIsOpen;
	bool			m_bIsFlag;

public:
	Block();
	virtual ~Block();

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	virtual void Draw() = 0;

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline void IsOpen()
	{
		m_bIsOpen = true;
	}

	inline bool GetIsFlag()
	{
		return m_bIsFlag;
	}
	inline void SetIsFlag(bool bFlag)
	{
		m_bIsFlag = bFlag;
	}

	inline BLOCK GetBlockKind()
	{
		return m_eBlock;
	}
};

class MineBlock : public Block
{
private:
	Bitmap		m_MineBlock;

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	void Draw();
};

class SafeBlock : public Block
{
private:
	Bitmap		m_NumberBlock;
	int				m_MineCount;

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	void NumberInit();
	void Draw();
};

