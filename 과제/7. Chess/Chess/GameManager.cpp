#include "GameManager.h"



GameManager::GameManager()
{
	m_BlockManager = NULL;
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
	m_Board = NULL;
}

// �ʱ�ȭ
void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_bFirstPlay = true;
	// ������ �÷��̾ ���� �����Ѵ�.
	m_Turn = TURN_BLACK;

	if (m_BlockManager != NULL)
	{
		delete m_BlockManager;
	}
	m_BlockManager = new BlockManager;

	if (m_PlayerBlack != NULL)
	{
		delete m_PlayerBlack;
	}
	m_PlayerBlack = new Player;
	m_PlayerBlack->Init(PLAYERCOLOR_BLACK);

	if (m_PlayerWhite != NULL)
	{
		delete m_PlayerWhite;
	}
	m_PlayerWhite = new Player;
	m_PlayerWhite->Init(PLAYERCOLOR_WHITE);

	SetBoardInit();
}

// ���� ����
void GameManager::SetBoardInit()
{
	// enum ���� �迭 �����Ҵ�
	// ���������� �ǽ��� ������ �� �ִ� ������ ã�� ����
	// �÷��̾� �ڽ��� �ǽ� ��ϻӸ� �ƴ϶� ���� �ǽ� ��ϱ��� ���� Ž���ؾ��ϱ� ������
	// �ܼ��� ���������� �ǽ��� ������ �� �ִ� �����ȿ�
	// ���� ���� �ǽ��� �ִ��� �������� �Ǵ��ϱ� ���� ����Ѵ�.
	if (m_Board != NULL)
	{
		for (int i = 0; i < BOARDY; i++)
		{
			delete[] m_Board[i];
		}
		delete m_Board;
	}
	m_Board = new BOARD*[BOARDY];
	for (int i = 0; i < BOARDY; i++)
	{
		m_Board[i] = new BOARD[BOARDX];
	}

	// �� �÷��̾ ���� �ǽ��� �ʱ� ��ġ ������ ���忡 �����Ѵ�.
	SetBoardInPieceInit(m_PlayerBlack);
	SetBoardInPieceInit(m_PlayerWhite);
}

// ���� ���� �ǽ��� ��ġ ������ �����Ѵ�.
void GameManager::SetBoardInPieceInit(Player * player)
{
	vector<Piece*> tmpPieceList = player->GetPieceList();
	PLAYERCOLOR tmpPlayerColor = player->GetPlayerColor();
	BOARD tmpBOARD;

	switch (tmpPlayerColor)
	{
	case PLAYERCOLOR_BLACK:
		tmpBOARD = BOARD_BLACK;
		break;
	case PLAYERCOLOR_WHITE:
		tmpBOARD = BOARD_WHITE;
		break;
	}

	// ���Ͱ� ������� ������ ���忡 �ǽ��� ��ġ ������ �����Ѵ�.
	if (!tmpPieceList.empty())
	{
		vector<Piece*>::size_type i = 0;
		POINT tmpPoint;
		for (i; i < tmpPieceList.size(); ++i)
		{
			tmpPoint = tmpPieceList[i]->GetPoint();
			m_Board[tmpPoint.x][tmpPoint.y] = tmpBOARD;
		}
	}
}

// �ʱ� ������ ������ ������ ������� ���带 �׸���.
void GameManager::DrawInitBoard()
{
	m_BlockManager->DrawAllBoard();
}


GameManager::~GameManager()
{
	delete m_PlayerBlack;
	delete m_PlayerWhite;
	for (int i = 0; i < BOARDY; i++)
	{
		delete[] m_Board[i];
	}
	delete m_Board;
}
