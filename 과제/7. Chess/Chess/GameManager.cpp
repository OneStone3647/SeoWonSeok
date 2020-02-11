#include "GameManager.h"



GameManager::GameManager()
{
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
	m_Board = NULL;
}

// 초기화
void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_bFirstPlay = true;
	// 검은색 플레이어가 먼저 시작한다.
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

// 보드 설정
void GameManager::SetBoardInit()
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
			m_Board[row][column].Init(row, column);
		}
	}

	// 각 플레이어가 가진 피스의 초기 위치 정보를 보드에 저장한다.
	SetBoardInPieceInit(m_PlayerBlack);
	SetBoardInPieceInit(m_PlayerWhite);
}

// 보드 위의 피스의 위치 정보를 저장한다.
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

// 초기 설정한 보드의 정보를 기반으로 보드를 그린다.
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
		// 선택한 피스가 없을 경우
		if (m_PlayerBlack->GetSelectPiece() == NULL)
		{
			// 마우스 포인터의 위치에 해당하는 피스를 선택한다.
			if (m_PlayerBlack->SelectPieceInPoint(m_PlayerBlack->GetMousePoint()))
			{
				BlockManager::GetInstance()->DrawSelectBoard(m_PlayerBlack->GetSelectPiece()->GetPoint());
			}
		}
		// 선택한 피스가 있을 경우
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
