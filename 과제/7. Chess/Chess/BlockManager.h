#pragma once
#include "Piece.h"

#define FIELDCOUNTMAX 3		// �ʵ��� ����
#define PIECECOUNTMAX 6		// ���� ����

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
	void DrawField();
	void DrawSelectField(POINT point);
	void SetPiece();
	void DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, int x, int y);
	void DrawInitPiece(vector<Piece*> pieceList);

	~BlockManager();
};

