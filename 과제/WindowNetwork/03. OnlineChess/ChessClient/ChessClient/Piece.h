#pragma once
#include "Mecro.h"
#include "Bitmap.h"

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
	HDC				m_MemDC;
	Bitmap			m_Bitmap;
	PIECECOLOR		m_PieceColor;
	PIECETYPE		m_PieceType;
	POINT				m_Point;			// 피스의 좌표
	RECT				m_Rect;			// 피스의 선택 범위
	bool				m_bIsLive;		// 피스가 살아 있는지 여부를 나타내는 변수

public:
	Piece();
	virtual ~Piece();

public:
	void Init(HDC MemDC, PIECECOLOR pieceColor, int x, int y);
	void SetPieceBitmap(PIECECOLOR pieceColor, PIECETYPE pieceType);

public:
	virtual bool CanMove(POINT point);

public:
	inline void Draw()
	{
		m_Bitmap.Draw(m_MemDC, m_Point.x * BLOCKBIT_X, m_Point.y * BLOCKBIT_Y);
	}

	inline Bitmap GetBitmap()
	{
		return m_Bitmap;
	}

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
		m_Rect = { BLOCKBIT_X * m_Point.x, BLOCKBIT_Y * m_Point.y, (BLOCKBIT_X * m_Point.x) + BLOCKBIT_X, (BLOCKBIT_Y * m_Point.y) + BLOCKBIT_Y };
	}

	inline bool GetLiveFlag()
	{
		return m_bIsLive;
	}
	inline void SetLiveFlag(bool bFlag)
	{
		m_bIsLive = bFlag;
	}
};

class Pawn : public Piece
{
public:
	Pawn();
	virtual ~Pawn();

public:
	bool CanMove(POINT point);
	bool CanAttack(POINT point);
};

class Knight : public Piece
{
public:
	Knight();
	virtual ~Knight();

public:
	bool CanMove(POINT point);
};

class Bishop : public Piece
{
public:
	Bishop();
	virtual ~Bishop();

public:
	bool CanMove(POINT point);
};

class Rook : public Piece
{
public:
	Rook();
	virtual ~Rook();

public:
	bool CanMove(POINT point);
};

class Queen : public Piece
{
public:
	Queen();
	virtual ~Queen();

public:
	bool CanMove(POINT point);
};

class King : public Piece
{
public:
	King();
	virtual ~King();

public:
	bool CanMove(POINT point);
};

