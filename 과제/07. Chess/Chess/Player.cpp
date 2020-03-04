#include "Player.h"



Player::Player()
{
	// 피스의 목록의 원소를 저장할 크기를 설정한다.
	m_PieceList.reserve(PIECEMAX);
}

// 초기화
void Player::Init(PLAYERCOLOR playerColor)
{
	m_PlayerColor = playerColor;

	// m_PieceList 백터가 비어 있지 않을 경우 초기화
	if (!m_PieceList.empty())
	{
		m_PieceList.clear();
	}
	SetPiece();

	m_SelectPiece = NULL;

	m_State = STATE_IDLE;
}

// 플레이어의 색에 따라 피스의 목록에 저장한다.
void Player::SetPiece()
{
	// 폰 저장
	for (int x = 0; x < 8; x++)
	{
		Piece* tmpPiece = new Pawn;
		switch (m_PlayerColor)
		{
		case PIECECOLOR_BLACK:
			tmpPiece->Init(PIECECOLOR_BLACK, x, 6);
			m_PieceList.push_back(tmpPiece);
			break;
		case PIECECOLOR_WHITE:
			tmpPiece->Init(PIECECOLOR_WHITE, x, 1);
			m_PieceList.push_back(tmpPiece);
			break;
		}
	}

	// 나이트 저장
	for (int x = 1; x <= 6; x += 5)
	{
		Piece* tmpKnight = new Knight;
		switch (m_PlayerColor)
		{
		case PIECECOLOR_BLACK:
			tmpKnight->Init(PIECECOLOR_BLACK, x, 7);
			m_PieceList.push_back(tmpKnight);
			break;
		case PIECECOLOR_WHITE:
			tmpKnight->Init(PIECECOLOR_WHITE, x, 0);
			m_PieceList.push_back(tmpKnight);
			break;
		}
	}

	// 비숍 저장
	for (int x = 2; x <= 5; x += 3)
	{
		Piece* tmpBishop = new Bishop;
		switch (m_PlayerColor)
		{
		case PIECECOLOR_BLACK:
			tmpBishop->Init(PIECECOLOR_BLACK, x, 7);
			m_PieceList.push_back(tmpBishop);
			break;
		case PIECECOLOR_WHITE:
			tmpBishop->Init(PIECECOLOR_WHITE, x, 0);
			m_PieceList.push_back(tmpBishop);
			break;
		}
	}

	// 룩 저장
	for (int x = 0; x <= 7; x += 7)
	{
		Piece* tmpRook = new Rook;
		switch (m_PlayerColor)
		{
		case PIECECOLOR_BLACK:
			tmpRook->Init(PIECECOLOR_BLACK, x, 7);
			m_PieceList.push_back(tmpRook);
			break;
		case PIECECOLOR_WHITE:
			tmpRook->Init(PIECECOLOR_WHITE, x, 0);
			m_PieceList.push_back(tmpRook);
			break;
		}
	}

	// 퀸 저장
	Piece* tmpQueen = new Queen;
	switch (m_PlayerColor)
	{
	case PIECECOLOR_BLACK:
		tmpQueen->Init(PIECECOLOR_BLACK, 3, 7);
		m_PieceList.push_back(tmpQueen);
		break;
	case PIECECOLOR_WHITE:
		tmpQueen->Init(PIECECOLOR_WHITE, 4, 0);
		m_PieceList.push_back(tmpQueen);
		break;
	}

	// 킹 저장
	Piece* tmpKing = new King;
	switch (m_PlayerColor)
	{
	case PIECECOLOR_BLACK:
		tmpKing->Init(PIECECOLOR_BLACK, 4, 7);
		m_PieceList.push_back(tmpKing);
		break;
	case PIECECOLOR_WHITE:
		tmpKing->Init(PIECECOLOR_WHITE, 3, 0);
		m_PieceList.push_back(tmpKing);
		break;
	}
}

void Player::Input(LPARAM lParam)
{
	m_State = STATE_PLAY;

	m_MousePoint.x = LOWORD(lParam);
	m_MousePoint.y = HIWORD(lParam);

	SetMousePointInBaord(m_MousePoint);
}

// 선택한 포인트 안에 자신의 피스가 있으며 살아 있을 경우 선택한다.
bool Player::SelectPieceInPoint(POINT point)
{
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if (PtInRect(&(m_PieceList[i]->GetRect()), point) && m_PieceList[i]->GetLiveFlag())
		{
			m_SelectPiece = m_PieceList[i];
			return true;
		}
	}

	m_SelectPiece = NULL;
	return false;
}

bool Player::CheckPieceInPoint(POINT point)
{
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if (PtInRect(&(m_PieceList[i]->GetRect()), point) && m_PieceList[i]->GetLiveFlag())
		{
			return true;
		}
	}

	return false;
}


Player::~Player()
{
	// 백터의 원소를 제거한다.
	m_PieceList.clear();
	// swap을 사용하여 vector의 capacity를 0으로 만든다.
	vector<Piece*>().swap(m_PieceList);
}
