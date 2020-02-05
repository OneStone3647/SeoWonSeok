#pragma once
#include <Windows.h>

enum BLOCKTYPE
{
	BLOCKTYPE_FIELD01 = 1,
	BLOCKTYPE_FIELD02,
	BLOCKTYPE_SELECT,
	BLOCKTYPE_BLACK,
	BLOCKTYPE_WITHE
};

// Ã¼½º¸» enum
enum PIECETYPE
{
	PIECETYPE_NONE = 0,
	PIECETYPE_KING,
	PIECETYPE_QUEEN,
	PIECETYPE_BISHOP,
	PIECETYPE_KNIGHT,
	PIECETYPE_ROOK,
	PIECETYPE_PAWN
};

class Block
{
private:
	HDC			MemDC;
	int			m_X;
	int			m_Y;
	BLOCKTYPE	m_BlockType;
	PIECETYPE	m_PieceType;
	HBITMAP		m_NewBlock;
	HBITMAP		m_OldBlock;

public:
	Block();
	
	void Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, PIECETYPE pieceType = PIECETYPE_NONE);
	void Draw(HDC hdc, int x, int y);

	void SetBlockType(BLOCKTYPE BlockType)
	{
		m_BlockType = BlockType;
	}
	BLOCKTYPE GetBlockType()
	{
		return m_BlockType;
	}

	void SetPieceType(PIECETYPE PieceType)
	{
		m_PieceType = PieceType;
	}
	PIECETYPE GetPieceType()
	{
		return m_PieceType;
	}

	~Block();
};

