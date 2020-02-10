#pragma once
#include "Mecro.h"

// 피스의 색
enum PIECECOLOR
{
	PIECECOLOR_BLACK = 0,
	PIECECOLOR_WHITE
};

// 피스의 종류
enum PIECETYPE
{
	PIECETYPE_PAWN = 0,
	PIECETYPE_KNIGHT,
	PIECETYPE_BISHOP,
	PIECETYPE_ROOK,
	PIECETYPE_QUEEN,
	PIECETYPE_KING
};

class Piece
{
protected:
	PIECECOLOR		m_PieceColor;
	PIECETYPE		m_PieceType;
	POINT			m_Point;			// 피스의 좌표
	RECT			m_Rect;				// 피스의 범위
	bool			m_bLive;			// 피스가 살아있는지 여부

public:
	Piece();

	void Init(PIECECOLOR pieceColor, int x, int y);
	virtual bool Move(POINT point);

	~Piece();

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

	inline bool GetLiveFlag()
	{
		return m_bLive;
	}
	inline void SetLiveFlag(bool bFlag)
	{
		m_bLive = bFlag;
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

