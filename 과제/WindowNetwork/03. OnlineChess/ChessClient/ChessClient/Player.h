#pragma once
#include "Piece.h"

class Player
{
private:
	HDC					m_MemDC;
	PIECECOLOR			m_PieceColor;
	vector<Piece*>		m_PieceList;			// 플레이어가 가진 피스의 목록입니다.
	Piece*					m_SelectPiece;		// 플레이어가 선택한 피스입니다.
	POINT					m_MousePoint;		// 선택한 위치를 나타내는 포인트입니다.
	Bitmap				m_SelectBitmap;

public:
	Player();
	~Player();

public:
	void Init(HDC MemDC, PIECECOLOR pieceColor);
	void Release();
	void InitPieceList(PIECECOLOR pieceColor);
	bool Input(LPARAM lParam);
	Piece*	SearchPiece(POINT point);
	Piece* SearchPieceinPoint(POINT point);
	bool SelectPiece(POINT point);
	void DrawAllPiece();
	bool GetKingIsLive();

public:
	inline POINT GetMousePoint()
	{
		return m_MousePoint;
	}
	inline void SetMousePoint(int x, int y)
	{
		m_MousePoint = { x, y };
	}

	inline	void DrawSelectBitmap(POINT point)
	{
		m_SelectBitmap.Draw(m_MemDC, point.x * BLOCKBIT_X, point.y * BLOCKBIT_Y);
	}

	inline int GetPieceColor()
	{
		return m_PieceColor;
	}

	inline Piece* GetSelectPiece()
	{
		return m_SelectPiece;
	}
	inline void ReleaseSelectPiece()
	{
		m_SelectPiece = nullptr;
	}

	inline vector<Piece*> GetPieceList()
	{
		return m_PieceList;
	}

	inline POINT GetBoardPoint()
	{
		return { m_MousePoint.x / BLOCKBIT_X, m_MousePoint.y / BLOCKBIT_Y };
	}
};

