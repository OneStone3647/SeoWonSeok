#include "Player.h"



Player::Player()
{
	// �ǽ��� ����� ���Ҹ� ������ ũ�⸦ �����մϴ�.
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
	// Piece Ŭ���� ������ ���� �Ҵ��� �����մϴ�.
	if (!m_PieceList.empty())
	{
		vector<Piece*>::iterator iter;
		for (iter = m_PieceList.begin(); iter != m_PieceList.end(); iter++)
		{
			delete (*iter);
		}
		m_PieceList.clear();
		// swap�� capacity�� 0���� ����� �ݴϴ�.
		vector<Piece*>().swap(m_PieceList);
	}
}

// �÷��̾��� ���� ���� �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����Ѵ�.
void Player::InitPieceList(PIECECOLOR pieceColor)
{
	// Piece Ŭ���� ���Ͱ� �̹� ������ ��� �Ҵ� �����մϴ�.
	Release();

	// �� �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

	// ����Ʈ �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

	// ��� �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

	// �� �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

	// �� �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

	// ŷ �ǽ��� �ʱ�ȭ�ϰ� ��Ͽ� �����մϴ�.
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

// ���콺 �����Ϳ� �ش��ϴ� �ǽ��� Ž���մϴ�.
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

// �ܼ� ����Ʈ( ex) (1, 1))�� �ش��ϴ� �ǽ��� Ž���մϴ�.
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

// �����Ϳ� �ش��ϴ� �ǽ��� �����մϴ�.
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
	// ŷ�� ���� �������� ����Ǿ� �ִ�.
	if (m_PieceList[15]->GetLiveFlag())
	{
		return true;
	}
	else
	{
		return false;
	}
}
