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
	m_Field = new Block[FIELDCOUNTMAX];
	SetField();

	if (m_BlackPiece != NULL)
	{
		delete[] m_BlackPiece;
	}
	m_BlackPiece = new Block[PIECECOUNTMAX];
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

void BlockManager::DrawSelectField(POINT point)
{
	m_Field[BLOCKTYPE_FIELD03].Draw(hdc, point.x, point.y);
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

void BlockManager::DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, int x, int y)
{
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		m_BlackPiece[pieceType].Draw(hdc, x, y);
		break;
	case PIECECOLOR_WHITE:
		m_WhitePiece[pieceType].Draw(hdc, x, y);
		break;
	}
}

void BlockManager::DrawInitPiece(vector<Piece*> pieceList)
{
	// 백터가 비어있지 않으면 그린다.
	if (!pieceList.empty())
	{
		for (int i = 0; i < PIECEMAX; i++)
		{
			DrawPiece(pieceList[i]->GetPieceColor(), pieceList[i]->GetPieceType(), pieceList[i]->GetPoint().x, pieceList[i]->GetPoint().y);
		}
	}
}

BlockManager::~BlockManager()
{
	delete[] m_Field;
	delete[] m_BlackPiece;
	delete[] m_WhitePiece;
}
