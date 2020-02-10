#include "Block.h"



Block::Block()
{
}

// 초기화
void Block::Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, BLOCKPIECETYPE blockPieceType)
{
	// 메모리DC 생성
	MemDC = CreateCompatibleDC(hdc);

	// 블록의 타입을 설정
	SetBlockType(blockType);

	// 블록의 타입이 검은색 피스 또는 흰색 피스일 경우
	if (m_BlockType == BLOCKTYPE_BLACK || m_BlockType == BLOCKTYPE_WHITE)
	{
		// 피스의 타입도 설정한다.
		SetBlockPieceType(blockPieceType);
	}

	// 새 비트맵 선택 및 이전 비트맵 저장
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_NewBitmap);
}

// 블록의 타입을 설정하고 해당 비트맵을 로드한다.
// 블록의 타입이 피스가 아닐 경우 피스의 타입을 PIECETYPE_NONE으로 설정한다.
// 블톡의 타입이 피스일 경우 따로 SetBlockPieceType 함수를 통해서 비트맵을 로드한다.
void Block::SetBlockType(BLOCKTYPE blockType)
{
	m_BlockType = blockType;
	switch (m_BlockType)
	{
		// 판 1
	case BLOCKTYPE_FIELD01:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block00.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// 판 2
	case BLOCKTYPE_FIELD02:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block01.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
		// 선택한 판의 테두리
	case BLOCKTYPE_FIELD03:
		m_BlockPieceType = BLOCKPIECETYPE_NONE;
		m_NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block02.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		break;
	}
}

// 피스의 타입을 설정하고 해당 비트맵을 로드한다.
// 블록의 타입에서 피스의 색에 따라 해당하는 피스의 비트맵을 로드한다.
void Block::SetBlockPieceType(BLOCKPIECETYPE blockPieceType)
{
	m_BlockPieceType = blockPieceType;
	// 피스의 색이 검은색일 경우
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
	// 피스의 색이 흰색일 경우
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

// 블록의 타입에 따라 그린다.
void Block::Draw(HDC hdc, int x, int y)
{
	// 블록의 타입이 보드판일 경우 원본 그대로 그린다.
	if (m_BlockType == BLOCKTYPE_FIELD01 || m_BlockType == BLOCKTYPE_FIELD02)
	{
		BitBlt(hdc, BLOCKX * x, BLOCKX *y, BLOCKX, BLOCKY, MemDC, 0, 0, SRCCOPY);
	}
	// 아닐 경우RGB(255, 0, 255)(핑크색)을 투명하게 만들고 그린다.
	else
	{
		TransparentBlt(hdc, BLOCKX * x, BLOCKX * y, BLOCKX, BLOCKY, MemDC, 0, 0, BLOCKX, BLOCKY, RGB(255, 0, 255));
	}
}


Block::~Block()
{
	SelectObject(MemDC, m_OldBitmap);	// 기존의 Bitmap을 선택한다.
	DeleteObject(m_NewBitmap);			// 새로 생성한 Bitmap을 삭제한다.
	DeleteDC(MemDC);					// 메모리DC를 삭제한다.
}
