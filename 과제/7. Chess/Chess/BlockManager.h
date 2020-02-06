#pragma once
#include "Block.h"

#define FIELDMAX 3		// �ʵ��� ����
#define PIECEMAX 6		// ���� ����

class BlockManager
{
private:
	HDC hdc;
	HINSTANCE m_hInst;

	Block* m_Field;
	Block* m_BlackPiece;
	Block* m_WhitePiece;

public:
	BlockManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetField();
	void DrawField(HDC hdc);
	void DrawInitPiece(HDC hdc);

	~BlockManager();
};

