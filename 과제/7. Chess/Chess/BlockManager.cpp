#include "BlockManager.h"



BlockManager::BlockManager()
{
	m_Field = NULL;
	m_BlackPiece = NULL;
	m_WhitePiece = NULL;
}

void BlockManager::Init(HWND hWnd, HINSTANCE hInst)
{
	hdc = GetDC(hWnd);
	m_hInst = hInst;

	if (m_Field != NULL)
	{
		delete[] m_Field;
	}
	m_Field = new Block[FIELDMAX];
	SetField();

	if (m_BlackPiece != NULL)
	{
		delete[] m_BlackPiece;
	}
	m_BlackPiece = new Block[PIECEMAX];
	if (m_WhitePiece != NULL)
	{
		delete[] m_WhitePiece;
	}
	m_WhitePiece = new Block[PIECEMAX];
	SetPiece();
}

void BlockManager::SetField()
{
	m_Field[BLOCKTYPE_FIELD01].Init(hdc, m_hInst, BLOCKTYPE_FIELD01);
	m_Field[BLOCKTYPE_FIELD02].Init(hdc, m_hInst, BLOCKTYPE_FIELD02);
	m_Field[BLOCKTYPE_FIELD03].Init(hdc, m_hInst, BLOCKTYPE_FIELD03);
}

void BlockManager::DrawField()
{
	for (int y = 0; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
	}
	for (int y = 1; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
	}
}

void BlockManager::SetPiece()
{
	m_BlackPiece[PIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_PAWN);
	m_BlackPiece[PIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_KNIGHT);
	m_BlackPiece[PIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_BISHOP);
	m_BlackPiece[PIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_ROOK);
	m_BlackPiece[PIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_QUEEN);
	m_BlackPiece[PIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_BLACK, PIECETYPE_KING);

	m_WhitePiece[PIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_PAWN);
	m_WhitePiece[PIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_KNIGHT);
	m_WhitePiece[PIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_BISHOP);
	m_WhitePiece[PIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_ROOK);
	m_WhitePiece[PIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_QUEEN);
	m_WhitePiece[PIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_WHITE, PIECETYPE_KING);
}

void BlockManager::DrawPiece(BLOCKTYPE blockType, PIECETYPE pieceType, int x, int y)
{
	switch (blockType)
	{
	case BLOCKTYPE_BLACK:
		m_BlackPiece[pieceType].Draw(hdc, x, y);
		break;
	case BLOCKTYPE_WHITE:
		m_WhitePiece[pieceType].Draw(hdc, x, y);
		break;
	}
}

void BlockManager::DrawInitPiece()
{
	// Æù
	for (int i = 0; i < 8; i++)
	{
		DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_PAWN, i, 6);
		DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_PAWN, i, 1);
	}

	// ³ªÀÌÆ®
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_KNIGHT, 1, 7);
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_KNIGHT, 6, 7);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_KNIGHT, 1, 0);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_KNIGHT, 6, 0);

	// ºñ¼ó
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_BISHOP, 2, 7);
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_BISHOP, 5, 7);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_BISHOP, 2, 0);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_BISHOP, 5, 0);

	// ·è
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_ROOK, 0, 7);
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_ROOK, 7, 7);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_ROOK, 0, 0);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_ROOK, 7, 0);

	// Äý
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_QUEEN, 3, 7);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_QUEEN, 4, 0);

	// Å·
	DrawPiece(BLOCKTYPE_BLACK, PIECETYPE_KING, 4, 7);
	DrawPiece(BLOCKTYPE_WHITE, PIECETYPE_KING, 3, 0);
}


BlockManager::~BlockManager()
{
}
