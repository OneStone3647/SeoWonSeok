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

	m_SelectPiece = NULL;

	m_SelectPoint.x = 0;
	m_SelectPoint.y = 0;

	m_State = STATE_IDLE;
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

	// ��� ����
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

	// �� ����
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

// ���콺�� ����Ʈ�� �ڽ��� ���� �ִ��� Ȯ���Ѵ�.
bool Player::CheckPieceInPoint(int x, int y)
{
	POINT MousePoint;
	MousePoint.x = x;
	MousePoint.y = y;
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if (PtInRect(&(m_PieceList[i]->GetRect()), MousePoint))
		{
			return true;
		}
	}
	return false;
}

Piece * Player::SelectPieceInPoint(int x, int y)
{
	POINT MousePoint;
	MousePoint.x = x;
	MousePoint.y = y;
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if (PtInRect(&(m_PieceList[i]->GetRect()), MousePoint))
		{
			return m_PieceList[i];
		}
	}
	return nullptr;
}

void Player::SetSelecetPoint(int x, int y)
{
	m_SelectPoint.x = x / BLOCKX;
	m_SelectPoint.y = y / BLOCKY;
}

void Player::Input(LPARAM lParam)
{
	m_State = STATE_PLAY;

	POINT MousePoint;
	MousePoint.x = LOWORD(lParam);
	MousePoint.y = HIWORD(lParam);

	SetSelecetPoint(MousePoint.x, MousePoint.y);

	// ������ ���� ���� ���
	if (m_SelectPiece == NULL)
	{
		// ���콺 ����Ʈ�� �ڽ��� ���� ���� ��� �����Ѵ�.
		if (CheckPieceInPoint(MousePoint.x, MousePoint.y))
		{
			m_SelectPiece = SelectPieceInPoint(MousePoint.x, MousePoint.y);
			BlockManager::GetInstance()->DrawSelectField(m_SelectPoint);
		}
	}
	// ������ ���� ���� ���
	else
	{
		// �̵��ϴ� ��ǥ�� �ڽ��� ���� ���� ������ �� �ִ� ��ǥ�� ���
		if (!CheckPieceInPoint(MousePoint.x, MousePoint.y) && m_SelectPiece->Move(m_SelectPoint))
		{
			BlockManager::GetInstance()->DeletePiece(m_SelectPiece->GetPoint());
			m_SelectPiece->SetPoint(m_SelectPoint);
			m_SelectPiece->SetRect();
			BlockManager::GetInstance()->DrawPiece(m_SelectPiece->GetPieceColor(), m_SelectPiece->GetPieceType(), m_SelectPoint);
			m_SelectPiece = NULL;
			m_State = STATE_IDLE;
		}
		// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
		else
		{
			BlockManager::GetInstance()->InitSelectField(m_SelectPiece->GetPieceColor(), m_SelectPiece->GetPieceType(), m_SelectPiece->GetPoint());
			m_SelectPiece = NULL;
		}
	}
}


Player::~Player()
{
	vector<Piece*>().swap(m_PieceList);		// swap�� ����� vector �޸� ����
}
