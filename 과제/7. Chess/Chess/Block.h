#pragma once
#include "Mecro.h"

// ����� ����
enum BLOCKTYPE
{
	BLOCKTYPE_FIELD01 = 0,
	BLOCKTYPE_FIELD02,
	BLOCKTYPE_FIELD03,		// ���� ���
	BLOCKTYPE_BLACK,		// ������ �ǽ�
	BLOCKTYPE_WHITE			// ��� �ǽ�
};

// �ǽ��� ����
enum BLOCKPIECETYPE
{
	BLOCKPIECETYPE_PAWN = 0,
	BLOCKPIECETYPE_KNIGHT,
	BLOCKPIECETYPE_BISHOP,
	BLOCKPIECETYPE_ROOK,
	BLOCKPIECETYPE_QUEEN,
	BLOCKPIECETYPE_KING,
	BLOCKPIECETYPE_NONE			// BLOCKTYPE�� BLOCKTYPE_BLACK �Ǵ� BLOCKTYPE_WHITE�� ��쿡 �ش�
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

