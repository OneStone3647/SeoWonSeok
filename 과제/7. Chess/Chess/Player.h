#pragma once
#include "Piece.h"

class Player
{
private:
	vector<Piece*> m_PieceList;

public:
	Player();

	void Init();
	void SetPiece(PIECECOLOR pieceColor);
	vector<Piece*> GetPieceList()
	{
		return m_PieceList;
	}
	void Input();

	~Player();
};

