#include "BoardManager.h"



BoardManager::BoardManager()
{
	m_Board = NULL;
}

void BoardManager::Init()
{
	// enum 이중 배열 동적할당
	// 보드위에서 피스가 움직을 수 있는 범위를 찾기 위해
	// 플레이어 자신의 피스 목록뿐만 아니라 적의 피스 목록까지 전부 탐색해야하기 때문에
	// 보드위에서 피스가 움직일 수 있는 범위안에
	// 무슨 색의 피스가 있는지 없는지만 판단하기 위해 사용한다.
	if (m_Board != NULL)
	{
		for (int i = 0; i < BOARDY; i++)
		{
			delete[] m_Board[i];
		}
		delete m_Board;
	}
	m_Board = new Board*[BOARDY];
	for (int i = 0; i < BOARDY; i++)
	{
		m_Board[i] = new Board[BOARDX];
	}

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			m_Board[row][column].SetBoardInfo(BOARDINFO_NONE);
		}
	}
}

void BoardManager::SetBoardInPieceInit(Player * player)
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
			m_Board[point.x][point.y].SetBoardInfo(boardInfo);
		}
	}
}

void BoardManager::MovePieceInBoard(POINT beforePoint, POINT afterPoint, BOARDINFO boardInfo)
{
	m_Board[beforePoint.x][beforePoint.y].SetBoardInfo(BOARDINFO_NONE);
	m_Board[afterPoint.x][afterPoint.y].SetBoardInfo(boardInfo);
}

bool BoardManager::CheckMoveInBoard(POINT currentPoint, POINT goalPoint)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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


BoardManager::~BoardManager()
{
	for (int i = 0; i < BOARDY; i++)
	{
		delete[] m_Board[i];
	}
	delete m_Board;
}
