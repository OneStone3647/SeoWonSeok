#pragma once
#include <Windows.h>
#include "Block.h"

#define PIECEMAX 16		// 말 최대 개수

// 절대값을 구하는 매크로.
#define ABVALUE(x) ((x) < 0 ? -(x) : (x))

enum PIECECOLOR
{
	PIECECOLOR_BLACK = 0,
	PIECECOLOR_WHITE
};

class Piece
{
protected:
	PIECECOLOR m_PieceColor;
	PIECETYPE m_PieceType;
	POINT m_Point;
	RECT m_Rect;
	bool m_bLive;

public:
	Piece();

	void Init(PIECECOLOR pieceColor, int x, int y);
	virtual bool Move(POINT point);
	~Piece();

public:
	inline PIECECOLOR GetPieceColor()
	{
		return m_PieceColor;
	}
	inline PIECETYPE GetPieceType()
	{
		return m_PieceType;
	}
	inline POINT GetPoint()
	{
		return m_Point;
	}
	inline void SetPoint(POINT point)
	{
		m_Point = point;
	}
	inline RECT GetRect()
	{
		return m_Rect;
	}
	inline void SetRect()
	{
		m_Rect = { BLOCKX * m_Point.x, BLOCKY * m_Point.y, (BLOCKX * m_Point.x) + BLOCKX, (BLOCKY * m_Point.y) + BLOCKY };
	}
};


class Pawn : public Piece
{
public:
	Pawn();

	bool Move(POINT point);

	~Pawn();
};


class Knight : public Piece
{
public:
	Knight();

	bool Move(POINT point);

	~Knight();
};


class Bishop : public Piece
{
public:
	Bishop();

	bool Move(POINT point);

	~Bishop();
};


class Rook : public Piece
{
public:
	Rook();

	bool Move(POINT point);

	~Rook();
};


class Queen : public Piece
{
public:
	Queen();

	bool Move(POINT point);

	~Queen();
};


class King : public Piece
{
public:
	King();

	bool Move(POINT point);

	~King();
};

