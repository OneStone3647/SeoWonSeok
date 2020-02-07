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
	virtual void Move() = 0;
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
	inline RECT GetRect()
	{
		return m_Rect;
	}
};


class Pawn : public Piece
{
public:
	Pawn();

	void Move();

	~Pawn();
};


class Knight : public Piece
{
public:
	Knight();

	void Move();

	~Knight();
};


class Bishop : public Piece
{
public:
	Bishop();

	void Move();

	~Bishop();
};


class Rook : public Piece
{
public:
	Rook();

	void Move();

	~Rook();
};


class Queen : public Piece
{
public:
	Queen();

	void Move();

	~Queen();
};


class King : public Piece
{
public:
	King();

	void Move();

	~King();
};

