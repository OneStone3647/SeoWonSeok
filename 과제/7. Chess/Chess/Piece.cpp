#include "Piece.h"



Piece::Piece()
{
}

void Piece::Init(PIECECOLOR pieceColor, int x, int y)
{
	m_PieceColor = pieceColor;
	m_Point.x = x;
	m_Point.y = y;
	m_Rect = { BLOCKX * x, BLOCKY * y, (BLOCKX * x) + BLOCKX, (BLOCKY * y) + BLOCKY };
}

Piece::~Piece()
{
}



Pawn::Pawn()
{
	m_PieceType = PIECETYPE_PAWN;
}

void Pawn::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

Pawn::~Pawn()
{
}



Knight::Knight()
{
	m_PieceType = PIECETYPE_KNIGHT;
}

void Knight::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

Knight::~Knight()
{
}



Bishop::Bishop()
{
	m_PieceType = PIECETYPE_BISHOP;
}

void Bishop::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

Bishop::~Bishop()
{
}



Rook::Rook()
{
	m_PieceType = PIECETYPE_ROOK;
}

void Rook::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

Rook::~Rook()
{
}



Queen::Queen()
{
	m_PieceType = PIECETYPE_QUEEN;
}

void Queen::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

Queen::~Queen()
{
}



King::King()
{
	m_PieceType = PIECETYPE_KING;
}

void King::Move(POINT point)
{
	SetPoint(point);
	SetRect();
}

King::~King()
{
}
