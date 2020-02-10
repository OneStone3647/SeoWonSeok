#pragma once
#include "Piece.h"
#include <vector>

using namespace std;

#define FIELDCOUNTMAX 3		// 필드의 종류
#define PIECECOUNTMAX 6		// 말의 종류

class BlockManager
{
private:
	static BlockManager* m_This;

public:
	static BlockManager* GetInstance()
	{
		if (m_This == NULL)
		{
			m_This = new BlockManager;
		}
		return m_This;
	}

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
	void DrawAllField();
	void DeletePiece(POINT point);
	void InitSelectField(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);
	void DrawSelectField(POINT point);
	void SetPiece();
	void DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point);
	void DrawInitPiece(vector<Piece*> pieceList);
	void Release();

	~BlockManager();
};

