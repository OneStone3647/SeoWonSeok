#include "Player.h"



Player::Player()
{
	m_PieceList.reserve(PIECEMAX);
}

void Player::Init()
{
	// m_PieceList ���Ͱ� ��� ���� ���� ��� �ʱ�ȭ
	if (!m_PieceList.empty())
	{
		m_PieceList.clear();
	}
}

void Player::SetPiece(PIECECOLOR pieceColor)
{
	// �� ����
	for (int x = 0; x < 8; x++)
	{
		Piece* tmpPiece = new Pawn;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpPiece->Init(pieceColor, x, 6);
			m_PieceList.push_back(tmpPiece);
			break;
		case PIECECOLOR_WHITE:
			tmpPiece->Init(pieceColor, x, 1);
			m_PieceList.push_back(tmpPiece);
			break;
		}
	}

	// ����Ʈ ����
	for (int x = 1; x <= 6; x += 5)
	{
		Piece* tmpPiece = new Knight;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpPiece->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpPiece);
			break;
		case PIECECOLOR_WHITE:
			tmpPiece->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpPiece);
			break;
		}
	}

	// ��� ����
	for (int x = 2; x <= 5; x += 3)
	{
		Piece* tmpPiece = new Bishop;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpPiece->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpPiece);
			break;
		case PIECECOLOR_WHITE:
			tmpPiece->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpPiece);
			break;
		}
	}

	// �� ����
	for (int x = 0; x <= 7; x += 7)
	{
		Piece* tmpPiece = new Rook;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpPiece->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpPiece);
			break;
		case PIECECOLOR_WHITE:
			tmpPiece->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpPiece);
			break;
		}
	}

	// �� ����
	Piece* tmpQueen = new Queen;
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		tmpQueen->Init(pieceColor, 3, 7);
		m_PieceList.push_back(tmpQueen);
		break;
	case PIECECOLOR_WHITE:
		tmpQueen->Init(pieceColor, 4, 0);
		m_PieceList.push_back(tmpQueen);
		break;
	}

	// ŷ ����
	Piece* tmpKing = new King;
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		tmpKing->Init(pieceColor, 4, 7);
		m_PieceList.push_back(tmpKing);
		break;
	case PIECECOLOR_WHITE:
		tmpKing->Init(pieceColor, 3, 0);
		m_PieceList.push_back(tmpKing);
		break;
	}
}

void Player::Input()
{
}


Player::~Player()
{
	vector<Piece*>().swap(m_PieceList);		// swap�� ����� vector �޸� ����
}
