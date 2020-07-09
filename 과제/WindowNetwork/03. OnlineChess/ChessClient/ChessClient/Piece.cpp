#include "Piece.h"



Piece::Piece()
{
}


Piece::~Piece()
{
}

void Piece::Init(HDC MemDC, PIECECOLOR pieceColor, int x, int y)
{
	m_MemDC = MemDC;
	m_PieceColor = pieceColor;
	m_Point.x = x;
	m_Point.y = y;
	SetRect();
	SetPieceBitmap(m_PieceColor, m_PieceType);
	m_bIsLive = true;
}

void Piece::SetPieceBitmap(PIECECOLOR pieceColor, PIECETYPE pieceType)
{
	// �ǽ��� ���� �������� ���
	if (pieceColor == PIECECOLOR_BLACK)
	{
		switch (pieceType)
		{
		case PIECETYPE_PAWN:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_00.bmp");
			break;
		case PIECETYPE_KNIGHT:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_01.bmp");
			break;
		case PIECETYPE_BISHOP:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_02.bmp");
			break;
		case PIECETYPE_ROOK:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_03.bmp");
			break;
		case PIECETYPE_QUEEN:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_04.bmp");
			break;
		case PIECETYPE_KING:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_b_05.bmp");
			break;
		}
	}
	// �ǽ��� ���� ����� ���
	else
	{
		switch (pieceType)
		{
		case PIECETYPE_PAWN:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_00.bmp");
			break;
		case PIECETYPE_KNIGHT:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_01.bmp");
			break;
		case PIECETYPE_BISHOP:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_02.bmp");
			break;
		case PIECETYPE_ROOK:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_03.bmp");
			break;
		case PIECETYPE_QUEEN:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_04.bmp");
			break;
		case PIECETYPE_KING:
			m_Bitmap.Init(m_MemDC, "Bitmap\\block_w_05.bmp");
			break;
		}
	}
}

bool Piece::CanMove(POINT point)
{
	// ������(8ĭ) �������� ������ �� �ֽ��ϴ�.
	if ((point.x >= 0 && point.x <= 7) && (point.y >= 0 && point.y <= 7))
	{
		// �ǽ� �ڽ��� �ִ� ������ ������ �� �����ϴ�.
		if (m_Point.x != point.x || m_Point.y != point.y)
		{
			return true;
		}
	}

	return false;
}

Pawn::Pawn()
{
	m_PieceType = PIECETYPE_PAWN;
}

Pawn::~Pawn()
{
}

bool Pawn::CanMove(POINT point)
{
	// �ڽ��� x�࿡�� ������ ���� �� �̵� �����մϴ�.
	if (m_Point.x == point.x)
	{
		switch (m_PieceColor)
		{
		case PIECECOLOR_BLACK:
			// ù �̵��� ��� 2ĭ �̵� �����մϴ�.
			if (m_Point.y == 6 && m_Point.y == point.y + 2)
			{
				return Piece::CanMove(point);
			}
			// ������ 1ĭ �̵��մϴ�.
			else if (m_Point.y == point.y + 1)
			{
				return Piece::CanMove(point);
			}
			break;
		case PIECECOLOR_WHITE:
			// ù �̵��� ��� 2ĭ �̵� �����մϴ�.
			if (m_Point.y == 1 && m_Point.y == point.y - 2)
			{
				return Piece::CanMove(point);
			}
			// ������ 1ĭ �̵��մϴ�.
			else if (m_Point.y == point.y - 1)
			{
				return Piece::CanMove(point);
			}
			break;
		}
	}

	return false;
}

bool Pawn::CanAttack(POINT point)
{
	switch (m_PieceColor)
	{
	case PIECECOLOR_BLACK:
		if (m_Point.y == point.y + 1)
		{
			// ������ �밢������ �̵� �����մϴ�.
			if (m_Point.x == point.x - 1)
			{
				return Piece::CanMove(point);
			}
			// ���� �밢������ �̵� �����մϴ�.
			else if (m_Point.x == point.x + 1)
			{
				return Piece::CanMove(point);
			}
		}
		break;
	case PIECECOLOR_WHITE:
		if (m_Point.y == point.y - 1)
		{
			// ������ �밢������ �̵� �����մϴ�.
			if (m_Point.x == point.x + 1)
			{
				return Piece::CanMove(point);
			}
			// ���� �밢������ �̵� �����մϴ�.
			else if (m_Point.x == point.x - 1)
			{
				return Piece::CanMove(point);
			}
		}
		break;
	}

	return false;
}

Knight::Knight()
{
	m_PieceType = PIECETYPE_KNIGHT;
}

Knight::~Knight()
{
}

bool Knight::CanMove(POINT point)
{
	if (ABVALUE(point.x - m_Point.x) == 2)
	{
		if (ABVALUE(point.y - m_Point.y) == 1)
		{
			return Piece::CanMove(point);
		}
	}
	else if (ABVALUE(point.y - m_Point.y) == 2)
	{
		if (ABVALUE(point.x - m_Point.x) == 1)
		{
			return Piece::CanMove(point);
		}
	}

	return false;
}

Bishop::Bishop()
{
	m_PieceType = PIECETYPE_BISHOP;
}

Bishop::~Bishop()
{
}

bool Bishop::CanMove(POINT point)
{
	if (ABVALUE(m_Point.x - point.x) == ABVALUE(m_Point.y - point.y))
	{
		return Piece::CanMove(point);
	}

	return false;
}

Rook::Rook()
{
	m_PieceType = PIECETYPE_ROOK;
}

Rook::~Rook()
{
}

bool Rook::CanMove(POINT point)
{
	if (m_Point.x == point.x)
	{
		return Piece::CanMove(point);
	}
	else if (m_Point.y == point.y)
	{
		return Piece::CanMove(point);
	}

	return false;
}

Queen::Queen()
{
	m_PieceType = PIECETYPE_QUEEN;
}

Queen::~Queen()
{
}

bool Queen::CanMove(POINT point)
{
	if (m_Point.x == point.x)
	{
		return Piece::CanMove(point);
	}
	else if (m_Point.y == point.y)
	{
		return Piece::CanMove(point);
	}
	else if (ABVALUE(m_Point.x - point.x) == ABVALUE(m_Point.y - point.y))
	{
		return Piece::CanMove(point);
	}

	return false;
}

King::King()
{
	m_PieceType = PIECETYPE_KING;
}

King::~King()
{
}

bool King::CanMove(POINT point)
{
	if (m_Point.x >= point.x - 1 && m_Point.x <= point.x + 1)
	{
		if (m_Point.y >= point.y - 1 && m_Point.y <= point.y + 1)
		{
			return Piece::CanMove(point);
		}
	}

	return false;
}
