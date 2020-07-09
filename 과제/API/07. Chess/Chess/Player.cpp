#include "Player.h"



Player::Player()
{
	// �ǽ��� ����� ���Ҹ� ������ ũ�⸦ �����Ѵ�.
	m_PieceList.reserve(PIECEMAX);
}

// �ʱ�ȭ
void Player::Init(PLAYERCOLOR playerColor)
{
	m_PlayerColor = playerColor;

	// m_PieceList ���Ͱ� ��� ���� ���� ��� �ʱ�ȭ
	if (!m_PieceList.empty())
	{
		m_PieceList.clear();
	}
	SetPiece();

	m_SelectPiece = NULL;

	m_State = STATE_IDLE;
}

// �÷��̾��� ���� ���� �ǽ��� ��Ͽ� �����Ѵ�.
void Player::SetPiece()
{
	// �� ����
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

	// ����Ʈ ����
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

	// ��� ����
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

	// �� ����
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

	// �� ����
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

	// ŷ ����
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

// ������ ����Ʈ �ȿ� �ڽ��� �ǽ��� ������ ��� ���� ��� �����Ѵ�.
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
	// ������ ���Ҹ� �����Ѵ�.
	m_PieceList.clear();
	// swap�� ����Ͽ� vector�� capacity�� 0���� �����.
	vector<Piece*>().swap(m_PieceList);
}
