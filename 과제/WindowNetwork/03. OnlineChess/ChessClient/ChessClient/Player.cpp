#include "Player.h"



Player::Player()
{
	// 피스의 목록의 원소를 저장할 크기를 설정합니다.
	//m_PieceList.reserve(PIECEMAX);
}


Player::~Player()
{
	Release();
}

void Player::Init(HDC MemDC, PIECECOLOR pieceColor)
{
	m_MemDC = MemDC;
	m_PieceColor = pieceColor;
	m_SelectPiece = nullptr;
	m_MousePoint = { -100, -100 };
	InitPieceList(m_PieceColor);
	m_SelectBitmap.Init(m_MemDC, "Bitmap\\block02.bmp");
}

void Player::Release()
{
	// Piece 클래스 벡터의 동적 할당을 해제합니다.
	if (!m_PieceList.empty())
	{
		vector<Piece*>::iterator iter;
		for (iter = m_PieceList.begin(); iter != m_PieceList.end(); iter++)
		{
			delete (*iter);
		}
		m_PieceList.clear();
		// swap을 capacity를 0으로 만들어 줍니다.
		vector<Piece*>().swap(m_PieceList);
	}
}

// 플레이어의 색에 따라 피스를 초기화하고 목록에 저장한다.
void Player::InitPieceList(PIECECOLOR pieceColor)
{
	// Piece 클래스 벡터가 이미 존재할 경우 할당 해제합니다.
	Release();

	// 폰 피스를 초기화하고 목록에 저장합니다.
	for (int x = 0; x < 8; x++)
	{
		Piece* tmpPawn = new Pawn;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpPawn->Init(m_MemDC, pieceColor, x, 6);
			m_PieceList.push_back(tmpPawn);
			break;
		case PIECECOLOR_WHITE:
			tmpPawn->Init(m_MemDC, pieceColor, x, 1);
			m_PieceList.push_back(tmpPawn);
			break;
		}
	}

	// 나이트 피스를 초기화하고 목록에 저장합니다.
	for (int x = 1; x <= 6; x += 5)
	{
		Piece* tmpKnight= new Knight;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpKnight->Init(m_MemDC, pieceColor, x, 7);
			m_PieceList.push_back(tmpKnight);
			break;
		case PIECECOLOR_WHITE:
			tmpKnight->Init(m_MemDC, pieceColor, x, 0);
			m_PieceList.push_back(tmpKnight);
			break;
		}
	}

	// 비숍 피스를 초기화하고 목록에 저장합니다.
	for (int x = 2; x <= 5; x += 3)
	{
		Piece* tmpBishop= new Bishop;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpBishop->Init(m_MemDC, pieceColor, x, 7);
			m_PieceList.push_back(tmpBishop);
			break;
		case PIECECOLOR_WHITE:
			tmpBishop->Init(m_MemDC, pieceColor, x, 0);
			m_PieceList.push_back(tmpBishop);
			break;
		}
	}

	// 룩 피스를 초기화하고 목록에 저장합니다.
	for (int x = 0; x <= 7; x += 7)
	{
		Piece* tmpRook= new Rook;
		switch (pieceColor)
		{
		case PIECECOLOR_BLACK:
			tmpRook->Init(m_MemDC, pieceColor, x, 7);
			m_PieceList.push_back(tmpRook);
			break;
		case PIECECOLOR_WHITE:
			tmpRook->Init(m_MemDC, pieceColor, x, 0);
			m_PieceList.push_back(tmpRook);
			break;
		}
	}

	// 퀸 피스를 초기화하고 목록에 저장합니다.
	Piece* tmpQueen = new Queen;
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		tmpQueen->Init(m_MemDC, pieceColor, 3, 7);
		m_PieceList.push_back(tmpQueen);
		break;
	case PIECECOLOR_WHITE:
		tmpQueen->Init(m_MemDC, pieceColor, 4, 0);
		m_PieceList.push_back(tmpQueen);
		break;
	}

	// 킹 피스를 초기화하고 목록에 저장합니다.
	Piece* tmpKing= new King;
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		tmpKing->Init(m_MemDC, pieceColor, 4, 7);
		m_PieceList.push_back(tmpKing);
		break;
	case PIECECOLOR_WHITE:
		tmpKing->Init(m_MemDC, pieceColor, 3, 0);
		m_PieceList.push_back(tmpKing);
		break;
	}
}

bool Player::Input(LPARAM lParam)
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
		return true;
	}
}

// 마우스 포인터에 해당하는 피스를 탐색합니다.
Piece * Player::SearchPiece(POINT point)
{
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if (PtInRect(&(m_PieceList[i]->GetRect()), point) && m_PieceList[i]->GetLiveFlag())
		{
			return m_PieceList[i];
		}
	}

	return nullptr;
}

// 단순 포인트( ex) (1, 1))에 해당하는 피스를 탐색합니다.
Piece * Player::SearchPieceinPoint(POINT point)
{
	vector<Piece*>::size_type i = 0;
	for (i; i < m_PieceList.size(); ++i)
	{
		if ((m_PieceList[i]->GetPoint().x == point.x && m_PieceList[i]->GetPoint().y == point.y)
			&& m_PieceList[i]->GetLiveFlag())
		{
			return m_PieceList[i];
		}
	}

	return nullptr;
}

// 포인터에 해당하는 피스를 선택합니다.
bool Player::SelectPiece(POINT point)
{
	Piece* tmpPiece = SearchPiece(point);
	if (tmpPiece == nullptr && m_SelectPiece == tmpPiece)
	{
		m_SelectPiece = nullptr;
		return false;
	}
	else
	{
		m_SelectPiece = tmpPiece;
		return true;
	}

	m_SelectPiece = nullptr;
	return false;
}

void Player::DrawAllPiece()
{
	vector<Piece*>::iterator iter;
	for (iter = m_PieceList.begin(); iter != m_PieceList.end(); ++iter)
	{
		if ((*iter)->GetLiveFlag())
		{
			(*iter)->Draw();
		}
	}

	//vector<Piece*>::size_type i = 0;
	//for (i; i < m_PieceList.size(); ++i)
	//{
	//	m_PieceList[i]->Draw();
	//}
}

bool Player::GetKingIsLive()
{	
	// 킹은 가장 마지막에 저장되어 있다.
	if (m_PieceList[15]->GetLiveFlag())
	{
		return true;
	}
	else
	{
		return false;
	}
}
