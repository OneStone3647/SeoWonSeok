#pragma once
#include "Player.h"

class BlockManager
{
private:
	HDC hdc;
	HINSTANCE m_hInst;
	Block* m_Field1;
	Block* m_Field2;
	HBITMAP NewBitmap;
	HBITMAP OldBitmap;
	int bX;
	int bY;

public:
	BlockManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBlock(Block* block);
	void DrawField();

	~BlockManager();
};

