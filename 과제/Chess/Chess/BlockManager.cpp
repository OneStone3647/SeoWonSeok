#include "BlockManager.h"



BlockManager::BlockManager()
{
}

void BlockManager::Init(HWND hWnd, HINSTANCE hInst)
{
	hdc = GetDC(hWnd);
	m_hInst = hInst;

	m_Field1 = new Block;
	m_Field1->Init();
	m_Field1->SetBlockType(BLOCKTYPE_FIELD01);
	SetFieldBlock(m_Field1);

	m_Field2 = new Block;
	m_Field2->Init();
	m_Field2->SetBlockType(BLOCKTYPE_FIELD02);
	SetFieldBlock(m_Field2);
}

void BlockManager::SetFieldBlock(Block* block)
{
	if (block->GetBlockType() == BLOCKTYPE_FIELD01)
	{
		NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block00.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		block->SetBlockImage(NewBitmap);
	}
	else if(block->GetBlockType() == BLOCKTYPE_FIELD02)
	{
		NewBitmap = (HBITMAP)LoadImage(NULL, TEXT("block01.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		block->SetBlockImage(NewBitmap);
	}
}

void BlockManager::DrawField()
{
}


BlockManager::~BlockManager()
{
}
