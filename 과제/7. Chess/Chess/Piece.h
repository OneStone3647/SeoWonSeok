#pragma once
#include <Windows.h>
#include <vector>
#include "Block.h"

using namespace std;

#define PIECEMAX 16		// 말 최대 개수

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

public:
	Piece();

	void Init(PIECECOLOR pieceColor, int x, int y);
	virtual void Move(POINT point) = 0;
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

	void Move(POINT point);

	~Pawn();
};


class Knight : public Piece
{
public:
	Knight();

	void Move(POINT point);

	~Knight();
};


class Bishop : public Piece
{
public:
	Bishop();

	void Move(POINT point);

	~Bishop();
};


class Rook : public Piece
{
public:
	Rook();

	void Move(POINT point);

	~Rook();
};


class Queen : public Piece
{
public:
	Queen();

	void Move(POINT point);

	~Queen();
};


class King : public Piece
{
public:
	King();

	void Move(POINT point);

	~King();
};

