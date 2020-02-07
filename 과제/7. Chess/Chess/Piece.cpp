#include "Piece.h"



Piece::Piece()
{
}

void Piece::Init(PIECECOLOR pieceColor, int x, int y)
{
	m_PieceColor = pieceColor;
	m_Point.x = x;
	m_Point.y = y;
}

Piece::~Piece()
{
}



Pawn::Pawn()
{
	m_PieceType = PIECETYPE_PAWN;
}

void Pawn::Move()
{
}

Pawn::~Pawn()
{
}



Knight::Knight()
{
	m_PieceType = PIECETYPE_KNIGHT;
}

void Knight::Move()
{
}

Knight::~Knight()
{
}



Bishop::Bishop()
{
	m_PieceType = PIECETYPE_BISHOP;
}

void Bishop::Move()
{
}

Bishop::~Bishop()
{
}



Rook::Rook()
{
	m_PieceType = PIECETYPE_ROOK;
}

void Rook::Move()
{
}

Rook::~Rook()
{
}



Queen::Queen()
{
	m_PieceType = PIECETYPE_QUEEN;
}

void Queen::Move()
{
}

Queen::~Queen()
{
}



King::King()
{
	m_PieceType = PIECETYPE_KING;
}

void King::Move()
{
}

King::~King()
{
}
