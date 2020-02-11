#include "GameManager.h"



GameManager::GameManager()
{
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

	BlockManager::GetInstance()->Init(hWnd, hInst);

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
			m_Board[row][column].Init(row, column);
		}
	}

	// �� �÷��̾ ���� �ǽ��� �ʱ� ��ġ ������ ���忡 �����Ѵ�.
	SetBoardInPieceInit(m_PlayerBlack);
	SetBoardInPieceInit(m_PlayerWhite);
}

// ���� ���� �ǽ��� ��ġ ������ �����Ѵ�.
void GameManager::SetBoardInPieceInit(Player * player)
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

// �ʱ� ������ ������ ������ ������� ���带 �׸���.
void GameManager::DrawInitBoard()
{
	BlockManager::GetInstance()->DrawAllBoard();
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerBlack->GetPieceList());
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerWhite->GetPieceList());
	m_bFirstPlay = false;
}

void GameManager::Input(LPARAM lParam)
{
	switch (m_Turn)
	{
	case TURN_BLACK:
		m_PlayerBlack->Input(lParam);
		// ������ �ǽ��� ���� ���
		if (m_PlayerBlack->GetSelectPiece() == NULL)
		{
			// ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����Ѵ�.
			if (m_PlayerBlack->SelectPieceInPoint(m_PlayerBlack->GetMousePoint()))
			{
				BlockManager::GetInstance()->DrawSelectBoard(m_PlayerBlack->GetSelectPiece()->GetPoint());
			}
		}
		// ������ �ǽ��� ���� ���
		else
		{

		}
		if (m_PlayerBlack->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_WHITE;
		}
		break;
	case TURN_WHITE:
		m_PlayerWhite->Input(lParam);
		if (m_PlayerWhite->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_BLACK;
		}
		break;
	}
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
	BlockManager::GetInstance()->Release();
}
