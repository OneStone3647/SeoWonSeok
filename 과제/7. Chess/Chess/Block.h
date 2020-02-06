#pragma once
#include <Windows.h>

#define BLOCKX 125
#define BLOCKY 125

enum BLOCKTYPE
{
	BLOCKTYPE_FIELD01 = 0,
	BLOCKTYPE_FIELD02,
	BLOCKTYPE_FIELD03,
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

	BLOCKTYPE	m_BlockType;
	PIECETYPE	m_PieceType;
	int			m_X;
	int			m_Y;

	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

public:
	Block();

	void Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, PIECETYPE pieceType = PIECETYPE_NONE);
	void SetBlockType(BLOCKTYPE blockType);
	void SetPieceType(PIECETYPE pieceType);
	void Draw(HDC hdc, int x, int y);

	~Block();
};

