#include "BlockManager.h"

BlockManager::BlockManager()
{
	m_BoardBlock = NULL;
	m_BlackPieceBlock = NULL;
	m_WhitePieceBlock = NULL;
	m_BoardInfoList = NULL;
}

void BlockManager::Init(HWND hWnd, HINSTANCE hInst)
{
	hdc = GetDC(hWnd);
	m_hInst = hInst;

	if (m_BoardBlock != NULL)
	{
		delete[] m_BoardBlock;
	}
	m_BoardBlock = new Block[FIELDCOUNTMAX];
	SetBoardBlock();

	if (m_BlackPieceBlock != NULL)
	{
		delete[] m_BlackPieceBlock;
	}
	m_BlackPieceBlock = new Block[PIECECOUNTMAX];
	if (m_WhitePieceBlock != NULL)
	{
		delete[] m_WhitePieceBlock;
	}
	m_WhitePieceBlock = new Block[PIECEMAX];
	SetPieceBlock();
	InvalidateRect(hWnd, NULL, TRUE);

	// ���������� �ǽ��� ������ �� �ִ� �����ȿ�
	// ���� ���� �ǽ��� �ִ��� �������� �Ǵ��ϱ� ���� ����Ѵ�.
	if (m_BoardInfoList != NULL)
	{
		delete[] m_BoardInfoList;
	}
	m_BoardInfoList = new BoardInfo[BOARDMAX];
	InitBoardList();
}

void BlockManager::SetBoardBlock()
{
	m_BoardBlock[BLOCKTYPE_FIELD01].Init(hdc, m_hInst, BLOCKTYPE_FIELD01);
	m_BoardBlock[BLOCKTYPE_FIELD02].Init(hdc, m_hInst, BLOCKTYPE_FIELD02);
	m_BoardBlock[BLOCKTYPE_FIELD03].Init(hdc, m_hInst, BLOCKTYPE_FIELD03);
}

void BlockManager::SetPieceBlock()
{
	m_BlackPieceBlock[BLOCKPIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_PAWN);
	m_BlackPieceBlock[BLOCKPIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_KNIGHT);
	m_BlackPieceBlock[BLOCKPIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_BISHOP);
	m_BlackPieceBlock[BLOCKPIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_ROOK);
	m_BlackPieceBlock[BLOCKPIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_QUEEN);
	m_BlackPieceBlock[BLOCKPIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_BLACK, BLOCKPIECETYPE_KING);

	m_WhitePieceBlock[BLOCKPIECETYPE_PAWN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_PAWN);
	m_WhitePieceBlock[BLOCKPIECETYPE_KNIGHT].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_KNIGHT);
	m_WhitePieceBlock[BLOCKPIECETYPE_BISHOP].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_BISHOP);
	m_WhitePieceBlock[BLOCKPIECETYPE_ROOK].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_ROOK);
	m_WhitePieceBlock[BLOCKPIECETYPE_QUEEN].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_QUEEN);
	m_WhitePieceBlock[BLOCKPIECETYPE_KING].Init(hdc, m_hInst, BLOCKTYPE_WHITE, BLOCKPIECETYPE_KING);
}

void BlockManager::DrawAllBoard()
{
	for (int y = 0; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
	}
	for (int y = 1; y < 8; y += 2)
	{
		for (int x = 0; x < 8; x += 2)
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, x, y);
		}
		for (int x = 1; x < 8; x += 2)
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, x, y);
		}
	}
}

void BlockManager::DrawPiece(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point)
{
	switch (pieceColor)
	{
	case PIECECOLOR_BLACK:
		m_BlackPieceBlock[pieceType].Draw(hdc, point.x, point.y);
		break;
	case PIECECOLOR_WHITE:
		m_WhitePieceBlock[pieceType].Draw(hdc, point.x, point.y);
		break;
	}
}

void BlockManager::ErasePiece(POINT point)
{
	// ¦�� ��
	if (point.x % 2 == 0)
	{
		// ¦�� ��
		if (point.y % 2 == 0)
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, point.x, point.y);
		}
		// Ȧ�� ��
		else
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, point.x, point.y);
		}
	}
	// Ȧ�� ��
	else
	{
		// ¦�� ��
		if (point.y % 2 == 0)
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, point.x, point.y);
		}
		// Ȧ�� ��
		else
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, point.x, point.y);
		}
	}
}

void BlockManager::DrawInitPiece(vector<Piece*> pieceList)
{
	// ���Ͱ� ������� ������ �׸���.
	if (!pieceList.empty())
	{
		for (int i = 0; i < PIECEMAX; i++)
		{
			DrawPiece(pieceList[i]->GetPieceColor(), pieceList[i]->GetPieceType(), pieceList[i]->GetPoint());
		}
	}
}

void BlockManager::DrawSelectBoard(POINT point)
{
	m_BoardBlock[BLOCKTYPE_FIELD03].Draw(hdc, point.x, point.y);
}

void BlockManager::EraseSelectBoard(PIECECOLOR pieceColor, PIECETYPE pieceType, POINT point)
{
	ErasePiece(point);
	DrawPiece(pieceColor, pieceType, point);
}

void BlockManager::InitBoardList()
{
	// ���� ����Ʈ �ʱ�ȭ
	int ListIndex = 0;
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			m_BoardInfoList[ListIndex].point.x = row;
			m_BoardInfoList[ListIndex].point.y = column;
			m_BoardInfoList[ListIndex].BoardInfo = BOARDINFO_NONE;
			ListIndex++;
		}
	}
}

void BlockManager::SetBoardInPieceInit(Player * player)
{
	vector<Piece*> pieceList = player->GetPieceList();
	PLAYERCOLOR playerColor = player->GetPlayerColor();
	BOARDINFO boardInfo;
	switch (playerColor)
	{
	case PLAYERCOLOR_BLACK:
		boardInfo = BOARDINFO_BLACK;
		break;
	case PLAYERCOLOR_WHITE:
		boardInfo = BOARDINFO_WHITE;
		break;
	}

	// ���Ͱ� ������� ������ ���忡 �ǽ��� ��ġ ������ �����Ѵ�.
	if (!pieceList.empty())
	{
		vector<Piece*>::size_type i = 0;
		POINT point;
		for (i; i < pieceList.size(); ++i)
		{
			point = pieceList[i]->GetPoint();
			SetBoardInfo(point, boardInfo);
		}
	}
}

void BlockManager::SetBoardInfo(POINT point, BOARDINFO boardInfo)
{
	SearchBoardInfoList(point)->BoardInfo = boardInfo;
}

BoardInfo * BlockManager::SearchBoardInfoList(POINT point)
{
	for (int i = 0; i < BOARDMAX; i++)
	{
		if (m_BoardInfoList[i].point.x == point.x && m_BoardInfoList[i].point.y == point.y)
		{
			return &(m_BoardInfoList[i]);
		}
	}
	return nullptr;
}

void BlockManager::MovePieceInBoard(POINT beforePoint, POINT afterPoint, BOARDINFO boardInfo)
{
	SetBoardInfo(beforePoint, BOARDINFO_NONE);
	SetBoardInfo(afterPoint, boardInfo);
}

bool BlockManager::CheckMoveInBoard(POINT currentPoint, POINT goalPoint)
{
	// ���� ��ġ�� ��ǥ ��ġ�� ���� ��� false
	if (currentPoint.x == goalPoint.x && currentPoint.y == goalPoint.y)
	{
		return false;
	}

	// ���� ��ġ�� ��ǥ ��ġ�� ��ĭ�� ���� ���̳��� ���
	if (currentPoint.x >= goalPoint.x - 1 && currentPoint.x <= goalPoint.x + 1)
	{
		if (currentPoint.y >= goalPoint.y - 1 && currentPoint.y <= goalPoint.y + 1)
		{
			return true;
		}
	}

	// ���� ��ǥ���� ��ǥ ��ǥ ������
	// �ڽ��� �ǽ� �Ǵ� ������ �ǽ� (��ֹ�)�� �ִ��� Ȯ���Ѵ�.

	// x��ǥ�� ���� ���
	if (currentPoint.x == goalPoint.x)
	{
		if (currentPoint.y > goalPoint.y)
		{
			// ��ǥ������ �̵��ϴ� �� ���尡 ������� ������ false;
			for (; currentPoint.y != goalPoint.y + 1;)
			{
				currentPoint.y--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
		else
		{
			// ��ǥ������ �̵��ϴ� �� ���尡 ������� ������ false;
			for (; currentPoint.y != goalPoint.y - 1;)
			{
				currentPoint.y++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
	}
	// y��ǥ�� ���� ���
	else if (currentPoint.y == goalPoint.y)
	{
		if (currentPoint.x > goalPoint.x)
		{
			// ��ǥ������ �̵��ϴ� �� ���尡 ������� ������ false;
			for (; currentPoint.x != goalPoint.x + 1;)
			{
				currentPoint.x--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
		else
		{
			// ��ǥ������ �̵��ϴ� �� ���尡 ������� ������ false;
			for (; currentPoint.x != goalPoint.x - 1;)
			{
				currentPoint.x++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
	}
	// x�� y �Ѵ� �ٸ� ���
	else
	{
		if (currentPoint.x > goalPoint.x && currentPoint.y > goalPoint.y)
		{
			for (; !(currentPoint.x == goalPoint.x + 1 && currentPoint.y == goalPoint.y + 1);)
			{
				currentPoint.x--;
				currentPoint.y--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
		else if (currentPoint.x < goalPoint.x && currentPoint.y < goalPoint.y)
		{
			for (; !(currentPoint.x == goalPoint.x - 1 && currentPoint.y == goalPoint.y - 1);)
			{
				currentPoint.x++;
				currentPoint.y++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
		else if (currentPoint.x > goalPoint.x && currentPoint.y < goalPoint.y)
		{
			for (; !(currentPoint.x == goalPoint.x + 1 && currentPoint.y == goalPoint.y - 1);)
			{
				currentPoint.x--;
				currentPoint.y++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
		else if (currentPoint.x < goalPoint.x && currentPoint.y > goalPoint.y)
		{
			for (; !(currentPoint.x == goalPoint.x - 1 && currentPoint.y == goalPoint.y + 1);)
			{
				currentPoint.x++;
				currentPoint.y--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// ��� �ִٸ� true;
			return true;
		}
	}
	return false;
}

BlockManager::~BlockManager()
{
	if (m_BoardBlock != NULL)
	{
		delete[] m_BoardBlock;
	}
	if (m_BlackPieceBlock != NULL)
	{
		delete[] m_BlackPieceBlock;
	}
	if (m_WhitePieceBlock != NULL)
	{
		delete[] m_WhitePieceBlock;
	}
	if (m_BoardInfoList != NULL)
	{
		delete[] m_BoardInfoList;
	}
}
