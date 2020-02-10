#include "Block.h"



Block::Block()
{
}

// �ʱ�ȭ
void Block::Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, BLOCKPIECETYPE blockPieceType)
{
	// �޸�DC ����
	MemDC = CreateCompatibleDC(hdc);

	// ����� Ÿ���� ����
	SetBlockType(blockType);

	// ����� Ÿ���� ������ �ǽ� �Ǵ� ��� �ǽ��� ���
	if (m_BlockType == BLOCKTYPE_BLACK || m_BlockType == BLOCKTYPE_WHITE)
	{
		// �ǽ��� Ÿ�Ե� �����Ѵ�.
		SetBlockPieceType(blockPieceType);
	}

	// �� ��Ʈ�� ���� �� ���� ��Ʈ�� ����
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);
}

// ����� Ÿ���� �����ϰ� �ش� ��Ʈ���� �ε��Ѵ�.
// ����� Ÿ���� �ǽ��� �ƴ� ��� �ǽ��� Ÿ���� PIECETYPE_NONE���� �����Ѵ�.
// ������ Ÿ���� �ǽ��� ��� ���� SetBlockPieceType �Լ��� ���ؼ� ��Ʈ���� �ε��Ѵ�.
void Block::SetBlockType(BLOCKTYPE blockType)
{
	m_BlockType = blockType;
	switch (m_BlockType)
	{
		// �� 1
	case BLOCKTYPE_FIELD01:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block00.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// �� 2
	case BLOCKTYPE_FIELD02:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block01.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// ������ ���� �׵θ�
	case BLOCKTYPE_FIELD03:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block02.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
	}
}

// �ǽ��� Ÿ���� �����ϰ� �ش� ��Ʈ���� �ε��Ѵ�.
// ����� Ÿ�Կ��� �ǽ��� ���� ���� �ش��ϴ� �ǽ��� ��Ʈ���� �ε��Ѵ�.
void Block::SetBlockPieceType(BLOCKPIECETYPE blockPieceType)
{
	m_BlockPieceType = blockPieceType;
	// �ǽ��� ���� �������� ���
	if (m_BlockType == BLOCKTYPE_BLACK)
	{
		switch (m_BlockPieceType)
		{
		case BLOCKPIECETYPE_PAWN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_00.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_KNIGHT:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_01.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_BISHOP:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_02.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_ROOK:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_03.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_QUEEN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_04.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_KING:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_b_05.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		}
	}
	// �ǽ��� ���� ����� ���
	else if(m_BlockType == BLOCKTYPE_WHITE)
	{
		switch (m_BlockPieceType)
		{
		case BLOCKPIECETYPE_PAWN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_00.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_KNIGHT:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_01.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_BISHOP:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_02.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_ROOK:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_03.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_QUEEN:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_04.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		case BLOCKPIECETYPE_KING:
			m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block_w_05.bmp"),
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			break;
		}
	}
}

// ����� Ÿ�Կ� ���� �׸���.
void Block::Draw(HDC hdc, int x, int y)
{
	// ����� Ÿ���� �������� ��� ���� �״�� �׸���.
	if (m_BlockType == BLOCKTYPE_FIELD01 || m_BlockType == BLOCKTYPE_FIELD02)
	{
		BitBlt(hdc, BLOCKX * x, BLOCKX *y, BLOCKX, BLOCKY, MemDC, 0, 0, SRCCOPY);
	}
	// �ƴ� ���RGB(255, 0, 255)(��ũ��)�� �����ϰ� ����� �׸���.
	else
	{
		TransparentBlt(hdc, BLOCKX * x, BLOCKX * y, BLOCKX, BLOCKY, MemDC, 0, 0, BLOCKX, BLOCKY, RGB(255, 0, 255));
	}
}


Block::~Block()
{
	SelectObject(MemDC, m_OldBitmap);	// ������ Bitmap�� �����Ѵ�.
	DeleteObject(m_NewBitmap);			// ���� ������ Bitmap�� �����Ѵ�.
	DeleteDC(MemDC);					// �޸�DC�� �����Ѵ�.
}
