#include "Block.h"



Block::Block()
{
}

void Block::Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, PIECETYPE pieceType)
{
	MemDC = CreateCompatibleDC(hdc);
	m_X = 0;
	m_Y = 0;

	SetBlockType(blockType);
	// ����� Ÿ���� ������ �� �Ǵ� ��� ���� ���
	if (m_BlockType == BLOCKTYPE_BLACK || m_BlockType == BLOCKTYPE_WITHE)
	{
		SetPieceType(pieceType);
	}
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);
}

// ����� Ÿ���� �����԰� ���ÿ� ��Ʈ���� �ε��Ѵ�.
// ������ Ÿ���� ���� ��� SetPieceType �Լ��� ���ؼ� ��Ʈ���� �ε��Ѵ�.
void Block::SetBlockType(BLOCKTYPE blockType)
{
	m_BlockType = blockType;
	switch (m_BlockType)
	{
		// �� 1
	case BLOCKTYPE_FIELD01:
		m_PieceType = PIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block00.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// �� 2
	case BLOCKTYPE_FIELD02:
		m_PieceType = PIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block01.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// ������ ���� �׵θ�
	case BLOCKTYPE_FIELD03:
		m_PieceType = PIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block02.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
	}
}

// ���� Ÿ���� �����Ѵ�.
// ����� Ÿ�Կ��� ���� ���� ���� �ش��ϴ� ���� ��Ʈ���� �ε��Ѵ�.
void Block::SetPieceType(PIECETYPE pieceType)
{
	m_PieceType = pieceType;
	// ���� ���� �������� ���
	if (m_BlockType == BLOCKTYPE_BLACK)
	{
		switch (m_PieceType)
		{
		case PIECETYPE_KING:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_05.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_QUEEN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_04.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_BISHOP:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_02.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_KNIGHT:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_01.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_ROOK:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_03.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_PAWN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_00.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		}
	}
	// ���� ���� ����� ���
	else
	{
		switch (m_PieceType)
		{
		case PIECETYPE_KING:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_05.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_QUEEN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_04.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_BISHOP:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_02.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_KNIGHT:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_01.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_ROOK:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_03.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case PIECETYPE_PAWN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_00.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		}
	}
}

void Block::Draw(HDC hdc, int x, int y)
{
	// ����� Ÿ���� ���� ��� ���� �״�� �׸���.
	if (m_BlockType == BLOCKTYPE_FIELD01 || m_BlockType == BLOCKTYPE_FIELD02)
	{
		BitBlt(hdc, x, y, BLOCKX, BLOCKY, MemDC, 0, 0, SRCCOPY);
	}
	// �ƴ� ���RGB(255, 0, 255)(��ũ��)�� �����ϰ� ����� �׸���.
	else
	{
		TransparentBlt(hdc, x, y, BLOCKX, BLOCKY, MemDC, 0, 0, BLOCKX, BLOCKY, RGB(255, 0, 255));
	}
}


Block::~Block()
{
	SelectObject(MemDC, m_OldBitmap);	// ������ Bitmap�� �����Ѵ�.
	DeleteObject(m_NewBitmap);			// ���� ������ Bitmap�� �����Ѵ�.
	DeleteDC(MemDC);					// �޸�DC�� �����Ѵ�.
}
