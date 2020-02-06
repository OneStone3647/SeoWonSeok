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
}

void BlockManager::SetField()
{
	m_Field[0].Init(hdc, m_hInst, BLOCKTYPE_FIELD01);
	m_Field[1].Init(hdc, m_hInst, BLOCKTYPE_FIELD02);
	m_Field[2].Init(hdc, m_hInst, BLOCKTYPE_FIELD03);
}

void BlockManager::DrawField(HDC hdc)
{
	for (int y = 0; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD01].Draw(hdc, BLOCKX * x, BLOCKY * y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD02].Draw(hdc, BLOCKX * x, BLOCKY * y);
		}
	}
	for (int y = 1; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD02].Draw(hdc, BLOCKX * x, BLOCKY * y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_Field[BLOCKTYPE_FIELD01].Draw(hdc, BLOCKX * x, BLOCKY * y);
		}
	}
}

void BlockManager::DrawInitPiece(HDC hdc)
{
}


BlockManager::~BlockManager()
{
}
