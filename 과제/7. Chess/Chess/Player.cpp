#include "Player.h"



Player::Player()
{
	m_PieceList.reserve(PIECEMAX);
}

void Player::Init()
{
	// m_PieceList 백터가 비어 있지 않을 경우 초기화
	if (!m_PieceList.empty())
	{
		m_PieceList.clear();
	}
}

void Player::SetPiece(PIECECOLOR pieceColor)
{
	// 폰 저장
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

	// 나이트 저장
	for (int x = 1; x <= 6; x += 5)
	{
		Piece* tmpKnight = new Knight;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpKnight->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpKnight);
			break;
		case PIECECOLOR_WHITE:
			tmpKnight->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpKnight);
			break;
		}
	}

	// 비숍 저장
	for (int x = 2; x <= 5; x += 3)
	{
		Piece* tmpBishop = new Bishop;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpBishop->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpBishop);
			break;
		case PIECECOLOR_WHITE:
			tmpBishop->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpBishop);
			break;
		}
	}

	// 룩 저장
	for (int x = 0; x <= 7; x += 7)
	{
		Piece* tmpRook = new Rook;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpRook->Init(pieceColor, x, 7);
			m_PieceList.push_back(tmpRook);
			break;
		case PIECECOLOR_WHITE:
			tmpRook->Init(pieceColor, x, 0);
			m_PieceList.push_back(tmpRook);
			break;
		}
	}

	// 퀸 저장
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

	// 킹 저장
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
	vector<Piece*>().swap(m_PieceList);		// swap을 사용한 vector 메모리 해제
}
