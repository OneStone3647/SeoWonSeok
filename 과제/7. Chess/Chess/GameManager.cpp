#include "GameManager.h"



GameManager::GameManager()
{
	m_BlockManager = NULL;
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

// 보드 설정
void GameManager::SetBoardInit()
{
	// enum 이중 배열 동적할당
	// 보드위에서 피스가 움직을 수 있는 범위를 찾기 위해
	// 플레이어 자신의 피스 목록뿐만 아니라 적의 피스 목록까지 전부 탐색해야하기 때문에
	// 단순히 보드위에서 피스가 움직일 수 있는 범위안에
	// 무슨 색의 피스가 있는지 없는지만 판단하기 위해 사용한다.
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

	// 각 플레이어가 가진 피스의 초기 위치 정보를 보드에 저장한다.
	SetBoardInPieceInit(m_PlayerBlack);
	SetBoardInPieceInit(m_PlayerWhite);
}

// 보드 위의 피스의 위치 정보를 저장한다.
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

	// 백터가 비어있지 않으면 보드에 피스의 위치 정보를 저장한다.
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

// 초기 설정한 보드의 정보를 기반으로 보드를 그린다.
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
