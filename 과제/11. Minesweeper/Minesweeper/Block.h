#pragma once
#include "Bitmap.h"

enum BLOCK
{
	BLOCK_NONE,
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
	bool			m_bFlag;

public:
	Block();
	virtual ~Block();

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	virtual void Draw() = 0;
	virtual void SetNumberBlock() = 0;

public:
	inline RECT GetCollision()
	{
		return m_Collision;
	}

	inline void IsOpen()
	{
		m_bIsOpen = true;
	}
	inline bool GetOpen()
	{
		return m_bIsOpen;
	}

	inline bool GetFlag()
	{
		return m_bFlag;
	}
	inline void SetFlag(bool bFlag)
	{
		m_bFlag = bFlag;
	}

	inline BLOCK GetBlockType()
	{
		return m_eBlock;
	}

	virtual inline void IncreaseMineCount() = 0;

	virtual inline int GetMineCount() = 0;
};

class MineBlock : public Block
{
private:
	Bitmap		m_MineBlock;

public:
	~MineBlock();
public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	void Draw();
	void SetNumberBlock()
	{
		return;
	}

public:
	inline void IncreaseMineCount()
	{
		return;
	}

	inline int GetMineCount()
	{
		return 0;
	}
};

class SafeBlock : public Block
{
private:
	Bitmap		m_NumberBlock;
	int				m_MineCount;

public:
	~SafeBlock();

public:
	void Init(HDC MemDC, int x, int y, int BlockStartX, int BlockStartY);
	void SetNumberBlock();
	void Draw();

public:
	inline void IncreaseMineCount()
	{
		m_MineCount++;
	}

	inline int GetMineCount()
	{
		return m_MineCount;
	}
};

