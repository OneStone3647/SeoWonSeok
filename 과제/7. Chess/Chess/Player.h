#pragma once
#include "Piece.h"

class Player
{
private:
	vector<Piece*> m_PieceList;
	Piece* m_SelectPiece;
public:
	Player();

	void Init();
	void SetPiece(PIECECOLOR pieceColor);
	bool SearchPiecePOINT(int x, int y);
	void Input();

	~Player();

public:
	inline	vector<Piece*> GetPieceList()
	{
		return m_PieceList;
	}
	inline Piece* GetSelectPiece()
	{
		return m_SelectPiece;
	}
};

