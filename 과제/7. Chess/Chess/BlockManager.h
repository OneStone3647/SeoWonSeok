#pragma once
#include "Block.h"
#include "Player.h"
#include <vector>

using namespace std;

#define FIELDCOUNTMAX 3		// 필드의 종류
#define PIECECOUNTMAX 6		// 피스의 종류

class BlockManager
{
private:
	HDC				hdc;
	HINSTANCE		m_hInst;

	Block*			m_Board;
	Block*			m_BlackPiece;
	Block*			m_WhitePiece;

public:
	BlockManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBoard();
	void SetPiece();
	void DrawAllBoard();
	void DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);
	void ErasePiece(POINT point);
	void DrawInitPiece(vector<Piece*> pieceList);
	void DrawSelectBoard(POINT point);
	void EraseSelectBoard(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);

	~BlockManager();
};

