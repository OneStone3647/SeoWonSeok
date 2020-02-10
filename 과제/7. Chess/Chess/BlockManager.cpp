#include "BlockManager.h"



BlockManager::BlockManager()
{
	m_Board = NULL;
	m_BlackPiece = NULL;
	m_WhitePiece = NULL;
}

void BlockManager::Init(HWND hWnd, HINSTANCE hInst)
{
	hdc = GetDC(hWnd);
	m_hInst = hInst;

	if (m_Board != NULL)
	{
		delete[] m_Board;
	}
	m_Board = new Block[FIELDCOUNTMAX];
	SetBoard();

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

void BlockManager::SetBoard()
{
	m_Board[BLOCKTYPE_FIELD01].Init(hdc, m_hInst, BLOCKTYPE_FIELD01);
	m_Board[BLOCKTYPE_FIELD02].Init(hdc, m_hInst, BLOCKTYPE_FIELD02);
	m_Board[BLOCKTYPE_FIELD03].Init(hdc, m_hInst, BLOCKTYPE_FIELD03);
}

void BlockManager::DrawAllBoard()
{
	for (int y = 0; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Board[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Board[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
	}
	for (int y = 1; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Board[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Board[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
	}
}

void BlockManager::SetPiece()
{
	m_BlackPiece[BLOCKPIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_PAWN);
	m_BlackPiece[BLOCKPIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_KNIGHT);
	m_BlackPiece[BLOCKPIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_BISHOP);
	m_BlackPiece[BLOCKPIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_ROOK);
	m_BlackPiece[BLOCKPIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_QUEEN);
	m_BlackPiece[BLOCKPIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_KING);

	m_WhitePiece[BLOCKPIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_PAWN);
	m_WhitePiece[BLOCKPIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_KNIGHT);
	m_WhitePiece[BLOCKPIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_BISHOP);
	m_WhitePiece[BLOCKPIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_ROOK);
	m_WhitePiece[BLOCKPIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_QUEEN);
	m_WhitePiece[BLOCKPIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_KING);
}

//void BlockManager::Release()
//{
//	delete m_This;
//}


BlockManager::~BlockManager()
{
}
