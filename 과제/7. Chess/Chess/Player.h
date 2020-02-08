#pragma once
#include "BlockManager.h"

class Player
{
private:
	vector<Piece*> m_PieceList;
	Piece* m_SelectPiece;
	POINT m_SelectPoint;

public:
	Player();

	void Init();
	void SetPiece(PIECECOLOR pieceColor);
	bool CheckPieceInPoint(int x, int y);
	Piece* SelectPieceInPoint(int x, int y);
	void SetSelecetPoint(int x, int y);
	void Input(LPARAM lParam);

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
	inline POINT GetSelectPoint()
	{
		return m_SelectPoint;
	}
};

