#include "Block.h"



Block::Block()
{
}

void Block::Init(HDC hdc, HINSTANCE hInst, BLOCKTYPE blockType, PIECETYPE pieceType)
{
	m_X = 0;
	m_Y = 0;
	m_BlockType = BLOCKTYPE_NONE;
	m_PieceType = PIECETYPE_NONE;

	if (block->GetBlockType() == BLOCKTYPE_FIELD01)
	{
		NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block00.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	else if (block->GetBlockType() == BLOCKTYPE_FIELD02)
	{
		NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block01.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
}

void Block::Draw(HDC hdc, int x, int y)
{
}


Block::~Block()
{
}
