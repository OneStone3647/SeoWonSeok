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

	m_SelectPiece = NULL;

	m_SelectPoint.x = 0;
	m_SelectPoint.y = 0;

	m_State = STATE_IDLE;
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

// 마우스의 포인트에 자신의 말이 있는지 확인한다.
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

	// 선택한 말이 없을 경우
	if (m_SelectPiece == NULL)
	{
		// 마우스 포인트에 자신의 말이 있을 경우 선택한다.
		if (CheckPieceInPoint(MousePoint.x, MousePoint.y))
		{
			m_SelectPiece = SelectPieceInPoint(MousePoint.x, MousePoint.y);
			BlockManager::GetInstance()->DrawSelectField(m_SelectPoint);
		}
	}
	// 선택한 말이 있을 경우
	else
	{
		// 이동하는 좌표에 자신의 말이 없고 움직일 수 있는 좌표일 경우
		if (!CheckPieceInPoint(MousePoint.x, MousePoint.y) && m_SelectPiece->Move(m_SelectPoint))
		{
			BlockManager::GetInstance()->DeletePiece(m_SelectPiece->GetPoint());
			m_SelectPiece->SetPoint(m_SelectPoint);
			m_SelectPiece->SetRect();
			BlockManager::GetInstance()->DrawPiece(m_SelectPiece->GetPieceColor(), m_SelectPiece->GetPieceType(), m_SelectPoint);
			m_SelectPiece = NULL;
			m_State = STATE_IDLE;
		}
		// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
		else
		{
			BlockManager::GetInstance()->InitSelectField(m_SelectPiece->GetPieceColor(), m_SelectPiece->GetPieceType(), m_SelectPiece->GetPoint());
			m_SelectPiece = NULL;
		}
	}
}


Player::~Player()
{
	vector<Piece*>().swap(m_PieceList);		// swap을 사용한 vector 메모리 해제
}
