#include "BoardManager.h"



BoardManager::BoardManager()
{
	m_Board = NULL;
}

void BoardManager::Init()
{
	// enum ���� �迭 �����Ҵ�
	// ���������� �ǽ��� ������ �� �ִ� ������ ã�� ����
	// �÷��̾� �ڽ��� �ǽ� ��ϻӸ� �ƴ϶� ���� �ǽ� ��ϱ��� ���� Ž���ؾ��ϱ� ������
	// ���������� �ǽ��� ������ �� �ִ� �����ȿ�
	// ���� ���� �ǽ��� �ִ��� �������� �Ǵ��ϱ� ���� ����Ѵ�.
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

	// ���Ͱ� ������� ������ ���忡 �ǽ��� ��ġ ������ �����Ѵ�.
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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
				if (m_Board[currentPoint.x][currentPoint.y].GetBoardInfo() != BOARDINFO_NONE)
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


BoardManager::~BoardManager()
{
	for (int i = 0; i < BOARDY; i++)
	{
		delete[] m_Board[i];
	}
	delete m_Board;
}
