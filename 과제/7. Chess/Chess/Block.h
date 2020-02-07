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
	BLOCKTYPE_WHITE
};

// Ã¼½º¸» enum
enum PIECETYPE
{
	PIECETYPE_PAWN = 0,
	PIECETYPE_KNIGHT,
	PIECETYPE_BISHOP,
	PIECETYPE_ROOK,
	PIECETYPE_QUEEN,
	PIECETYPE_KING,
	PIECETYPE_NONE
};

class Block
{
protected:
	HDC			MemDC;

private:

	BLOCKTYPE	m_BlockType;
	PIECETYPE	m_PieceType;

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

