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

	// 보드위에서 피스가 움직일 수 있는 범위안에
	// 무슨 색의 피스가 있는지 없는지만 판단하기 위해 사용한다.
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
	// 짝수 열
	if (point.x % 2 == 0)
	{
		// 짝수 행
		if (point.y % 2 == 0)
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, point.x, point.y);
		}
		// 홀수 행
		else
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, point.x, point.y);
		}
	}
	// 홀수 열
	else
	{
		// 짝수 행
		if (point.y % 2 == 0)
		{
			m_BoardBlock[BLOCKTYPE_FIELD02].Draw(hdc, point.x, point.y);
		}
		// 홀수 행
		else
		{
			m_BoardBlock[BLOCKTYPE_FIELD01].Draw(hdc, point.x, point.y);
		}
	}
}

void BlockManager::DrawInitPiece(vector<Piece*> pieceList)
{
	// 백터가 비어있지 않으면 그린다.
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
	// 보드 리스트 초기화
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

	// 백터가 비어있지 않으면 보드에 피스의 위치 정보를 저장한다.
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
	// 현재 위치와 목표 위치가 같은 경우 false
	if (currentPoint.x == goalPoint.x && currentPoint.y == goalPoint.y)
	{
		return false;
	}

	// 현재 위치와 목표 위치가 한칸씩 차이 나이나는 경우
	if (currentPoint.x >= goalPoint.x - 1 && currentPoint.x <= goalPoint.x + 1)
	{
		if (currentPoint.y >= goalPoint.y - 1 && currentPoint.y <= goalPoint.y + 1)
		{
			return true;
		}
	}

	// 현재 좌표에서 목표 좌표 전까지
	// 자신의 피스 또는 상대방의 피스 (장애물)이 있는지 확인한다.

	// x좌표가 같을 경우
	if (currentPoint.x == goalPoint.x)
	{
		if (currentPoint.y > goalPoint.y)
		{
			// 목표전까지 이동하는 중 보드가 비어있지 않으면 false;
			for (; currentPoint.y != goalPoint.y + 1;)
			{
				currentPoint.y--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// 비어 있다면 true;
			return true;
		}
		else
		{
			// 목표전까지 이동하는 중 보드가 비어있지 않으면 false;
			for (; currentPoint.y != goalPoint.y - 1;)
			{
				currentPoint.y++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// 비어 있다면 true;
			return true;
		}
	}
	// y좌표가 같을 경우
	else if (currentPoint.y == goalPoint.y)
	{
		if (currentPoint.x > goalPoint.x)
		{
			// 목표전까지 이동하는 중 보드가 비어있지 않으면 false;
			for (; currentPoint.x != goalPoint.x + 1;)
			{
				currentPoint.x--;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// 비어 있다면 true;
			return true;
		}
		else
		{
			// 목표전까지 이동하는 중 보드가 비어있지 않으면 false;
			for (; currentPoint.x != goalPoint.x - 1;)
			{
				currentPoint.x++;
				if (SearchBoardInfoList(currentPoint)->BoardInfo != BOARDINFO_NONE)
				{
					return false;
				}
			}

			// 비어 있다면 true;
			return true;
		}
	}
	// x와 y 둘다 다를 경우
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

			// 비어 있다면 true;
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

			// 비어 있다면 true;
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

			// 비어 있다면 true;
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

			// 비어 있다면 true;
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
