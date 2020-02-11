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
	m_bLive = true;
}

bool Piece::Move(POINT point)
{
	// 8칸 내에서만 움직일 수 있다.
	if ((point.x >= 0 && point.x <= 7) && (point.y >= 0 && point.y <= 7))
	{
		// 자기 자신이 있는 곳에는 움직일 수 없다.
		if (m_Point.x != point.x || m_Point.y != point.y)
		{
			return true;
		}
	}

	return false;
}

Piece::~Piece()
{
}



Pawn::Pawn()
{
	m_PieceType = PIECETYPE_PAWN;
}

bool Pawn::Move(POINT point)
{
	switch (m_PieceColor)
	{
	case PIECECOLOR_BLACK:
		if (m_Point.x == point.x)
		{
			// 첫 이동일 경우 2칸 이동 가능
			if (m_Point.y == 6 && m_Point.y == point.y + 2)
			{
				return Piece::Move(point);
			}
			else if (m_Point.y == point.y + 1)
			{
				return Piece::Move(point);
			}
		}
		break;
	case PIECECOLOR_WHITE:
		// 첫 이동일 경우 2칸 이동 가능
		if (m_Point.x == point.x)
		{
			// 첫 이동일 경우 2칸 이동 가능
			if (m_Point.y == 1 && m_Point.y == point.y - 2)
			{
				return Piece::Move(point);
			}
			else if (m_Point.y == point.y - 1)
			{
				return Piece::Move(point);
			}
		}
		break;
	}

	return false;
}

Pawn::~Pawn()
{
}



Knight::Knight()
{
	m_PieceType = PIECETYPE_KNIGHT;
}

bool Knight::Move(POINT point)
{
	if (ABVALUE(point.x - m_Point.x) == 2)
	{
		if (ABVALUE(point.y - m_Point.y) == 1)
		{
			return Piece::Move(point);
		}
	}
	else if (ABVALUE(point.y - m_Point.y) == 2)
	{
		if (ABVALUE(point.x - m_Point.x) == 1)
		{
			return Piece::Move(point);
		}
	}

	return false;
}

Knight::~Knight()
{
}



Bishop::Bishop()
{
	m_PieceType = PIECETYPE_BISHOP;
}

bool Bishop::Move(POINT point)
{
	if (ABVALUE(m_Point.x - point.x) == ABVALUE(m_Point.y - point.y))
	{
		return Piece::Move(point);
	}

	return false;
}

Bishop::~Bishop()
{
}



Rook::Rook()
{
	m_PieceType = PIECETYPE_ROOK;
}

bool Rook::Move(POINT point)
{
	if (m_Point.x == point.x)
	{
		return Piece::Move(point);
	}
	else if (m_Point.y == point.y)
	{
		return Piece::Move(point);
	}

	return false;
}

Rook::~Rook()
{
}



Queen::Queen()
{
	m_PieceType = PIECETYPE_QUEEN;
}

bool Queen::Move(POINT point)
{
	if (m_Point.x == point.x)
	{
		return Piece::Move(point);
	}
	else if (m_Point.y == point.y)
	{
		return Piece::Move(point);
	}
	else if (ABVALUE(m_Point.x - point.x) == ABVALUE(m_Point.y - point.y))
	{
		return Piece::Move(point);
	}

	return false;
}

Queen::~Queen()
{
}



King::King()
{
	m_PieceType = PIECETYPE_KING;
}

bool King::Move(POINT point)
{
	if (m_Point.x >= point.x - 1 && m_Point.x <= point.x + 1)
	{
		if (m_Point.y >= point.y - 1 && m_Point.y <= point.y + 1)
		{
			return Piece::Move(point);
		}
	}

	return false;
}

King::~King()
{
}
