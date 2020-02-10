#pragma once
#include "Mecro.h"

// 블록의 종류
enum BLOCKTYPE
{
	BLOCKTYPE_FIELD01 = 0,
	BLOCKTYPE_FIELD02,
	BLOCKTYPE_FIELD03,		// 선택 블록
	BLOCKTYPE_BLACK,		// 검은색 피스
	BLOCKTYPE_WHITE			// 흰색 피스
};

// 피스의 종류
enum BLOCKPIECETYPE
{
	BLOCKPIECETYPE_PAWN = 0,
	BLOCKPIECETYPE_KNIGHT,
	BLOCKPIECETYPE_BISHOP,
	BLOCKPIECETYPE_ROOK,
	BLOCKPIECETYPE_QUEEN,
	BLOCKPIECETYPE_KING,
	BLOCKPIECETYPE_NONE			// BLOCKTYPE이 BLOCKTYPE_BLACK 또는 BLOCKTYPE_WHITE일 경우에 해당
};

class Block
{
private:
	HDC				MemDC;

	BLOCKTYPE		m_BlockType;
	BLOCKPIECETYPE	m_BlockPieceType;

	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;

public:
	Block();

	void Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, BLOCKPIECETYPE blockPieceType = BLOCKPIECETYPE_NONE);
	void SetBlockType(BLOCKTYPE blockType);
	void SetBlockPieceType(BLOCKPIECETYPE blockPieceType);
	void Draw(HDC hdc, int x, int y);

	~Block();
};

