#include "GameManager.h"



GameManager::GameManager()
{
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
	m_BoardManager = NULL;
}

// 초기화
void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_hWnd = hWnd;
	m_hInst = hInst;
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

	if (m_BoardManager != NULL)
	{
		delete m_BoardManager;
	}
	m_BoardManager = new BoardManager;
	m_BoardManager->Init();
	// 각 플레이어가 가진 피스의 초기 위치 정보를 보드에 저장한다.
	m_BoardManager->SetBoardInPieceInit(m_PlayerBlack);
	m_BoardManager->SetBoardInPieceInit(m_PlayerWhite);
}

// 초기 보드와 피스를 그린다.
void GameManager::DrawInitBoard()
{
	BlockManager::GetInstance()->DrawAllBoard();
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerBlack->GetPieceList());
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerWhite->GetPieceList());
	m_bFirstPlay = false;
}

void GameManager::Input(LPARAM lParam)
{
	// 턴에 따라 현재 입력하는 플레이어를 전환한다.
	Player* CurrentPlayer = NULL;
	Player* EnemyPlayer = NULL;
	BOARDINFO CurrentBoardInfo;
	BOARDINFO EnemyBoardInfo;
	if (m_Turn == TURN_BLACK)
	{
		CurrentPlayer = m_PlayerBlack;
		EnemyPlayer = m_PlayerWhite;
		CurrentBoardInfo = BOARDINFO_BLACK;
		EnemyBoardInfo = BOARDINFO_WHITE;
	}
	else
	{
		CurrentPlayer = m_PlayerWhite;
		EnemyPlayer = m_PlayerBlack;
		CurrentBoardInfo = BOARDINFO_WHITE;
		EnemyBoardInfo = BOARDINFO_BLACK;
	}

	CurrentPlayer->Input(lParam);

	POINT MousePoint = CurrentPlayer->GetMousePoint();								// 픽셀로 된 마우스의 포인터 ex) (125, 250)
	POINT MousePointInBoard = CurrentPlayer->GetMousePointInBoard();			// 보드에 사용하는 마우스의 포인터 ex) (8, 4)
	Board** tmpBoard = m_BoardManager->GetBoard();

	// 선택한 피스가 없을 경우
	if (CurrentPlayer->GetSelectPiece() == NULL)
	{
		// 마우스 포인터의 위치에 해당하는 피스를 선택한다.
		if (CurrentPlayer->SelectPieceInPoint(MousePoint))
		{
			Piece* CurrentSelectPiece = CurrentPlayer->GetSelectPiece();							// 현재 선택된 피스
			BlockManager::GetInstance()->DrawSelectBoard(CurrentSelectPiece->GetPoint());
		}
	}
	// 선택한 피스가 있을 경우
	else
	{
		Piece* CurrentSelectPiece = CurrentPlayer->GetSelectPiece();							// 현재 선택된 피스
		// 선택한 피스가 나이트인 경우
		if (CurrentSelectPiece->GetPieceType() == PIECETYPE_KNIGHT)
		{
			// 이동하는 좌표에 자신의 말이 없고
			// 움직일 수 있는 좌표일 경우
			if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard))
			{
				Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
			}
			// 이동하는 좌표에 자신의 말이 있거나
			// 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
			else
			{
				EraseSelectBoard(CurrentSelectPiece);
			}
			CurrentPlayer->SetSelectPiece(NULL);
		}
		// 선택한 피스가 폰인 경우
		else if (CurrentSelectPiece->GetPieceType() == PIECETYPE_PAWN)
		{
			if (tmpBoard[MousePointInBoard.x][MousePointInBoard.y].GetBoardInfo() == EnemyBoardInfo)
			{
				// 다운캐스팅
				Pawn* tmpPawn = dynamic_cast<Pawn*>(CurrentSelectPiece);
				// 공격하는 좌표에 자신의 말이 없고
				// 공격할 수 있는 좌표일 경우
				if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && tmpPawn->Attack(MousePointInBoard))
				{
					Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
				}
				// 이동하는 좌표에 자신의 말이 있거나
				// 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
				else
				{
					EraseSelectBoard(CurrentSelectPiece);
				}
				CurrentPlayer->SetSelectPiece(NULL);
			}
			else
			{
				// 이동하는 좌표에 자신의 말이 없고
				// 움직일 수 있는 좌표일 경우
				if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard))
				{
					Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
				}
				// 이동하는 좌표에 자신의 말이 있거나
				// 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
				else
				{
					EraseSelectBoard(CurrentSelectPiece);
				}
				CurrentPlayer->SetSelectPiece(NULL);
			}
		}
		else
		{
			// 이동하는 좌표에 자신의 말이 없고
			// 움직일 수 있는 좌표이며
			// 이동하는 좌표 전까지 장애물이 없는 경우
			if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard) && m_BoardManager->CheckMoveInBoard(CurrentSelectPiece->GetPoint(), MousePointInBoard))
			{
				Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
			}
			// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
			else
			{
				EraseSelectBoard(CurrentSelectPiece);
			}
			CurrentPlayer->SetSelectPiece(NULL);
		}
	}

	// 킹은 15번에 저장되어있다.
	// 킹이 죽었을 경우 결과 창을 나타낸다.
	if (!EnemyPlayer->GetPieceList()[15]->GetLiveFlag())
	{
		if (EnemyPlayer->GetPlayerColor() == PLAYERCOLOR_BLACK)
		{
			if (MessageBox(m_hWnd, TEXT("백팀의 승리!!\n다시하시겠습니까?"), TEXT("Winner"), MB_YESNO) == IDYES)
			{
				Init(m_hWnd, m_hInst);
			}
			else
			{
				BlockManager::GetInstance()->Release();
				PostQuitMessage(0);
			}
		}
		else if (EnemyPlayer->GetPlayerColor() == PLAYERCOLOR_WHITE)
		{
			if (MessageBox(m_hWnd, TEXT("흑팀의 승리!!\n다시하시겠습니까?"), TEXT("Winner"), MB_YESNO) == IDYES)
			{
				Init(m_hWnd, m_hInst);
			}
			else
			{
				BlockManager::GetInstance()->Release();
				PostQuitMessage(0);
			}
		}
	}

	if (CurrentPlayer->GetState() == STATE_IDLE)
	{
		if (CurrentPlayer->GetPlayerColor() == PLAYERCOLOR_BLACK)
		{
			m_Turn = TURN_WHITE;
		}
		else
		{
			m_Turn = TURN_BLACK;
		}
	}
}

void GameManager::Move(Player * currentPlayer, Player* enemyPlayer, Piece * currentSelectPiece, POINT mousePoint, POINT mousePointInBoard, BOARDINFO currentBoardInfo, BOARDINFO enemyBoardInfo)
{
	Board** tmpBoard = m_BoardManager->GetBoard();

	// 이동하는 좌표에 상대방의 피스가 있을 경우
	if (tmpBoard[mousePointInBoard.x][mousePointInBoard.y].GetBoardInfo() == enemyBoardInfo)
	{
		vector<Piece*> EnemyPieceList = enemyPlayer->GetPieceList();
		vector<Piece*>::size_type i = 0;
		for (i; i < enemyPlayer->GetPieceList().size(); ++i)
		{
			if (EnemyPieceList[i]->GetPoint().x == mousePointInBoard.x && EnemyPieceList[i]->GetPoint().y == mousePointInBoard.y)
			{
				EnemyPieceList[i]->SetLiveFlag(false);
			}
		}
		tmpBoard[mousePointInBoard.x][mousePointInBoard.y].SetBoardInfo(BOARDINFO_NONE);
		BlockManager::GetInstance()->ErasePiece(mousePointInBoard);
	}

	// 보드의 정보를 입력한다.
	m_BoardManager->MovePieceInBoard(currentSelectPiece->GetPoint(), mousePointInBoard, currentBoardInfo);

	// 현재 선택한 피스 비트맵을 지운다.
	BlockManager::GetInstance()->ErasePiece(currentSelectPiece->GetPoint());

	// 현재 선택한 피스의 정보를 수정한다.
	currentSelectPiece->SetPoint(mousePointInBoard);
	currentSelectPiece->SetRect();

	// 수정된 피스의 정보를 바탕으로 피스를 그린다.
	BlockManager::GetInstance()->DrawPiece(currentSelectPiece->GetPieceColor(), currentSelectPiece->GetPieceType(), mousePointInBoard);

	currentPlayer->SetState(STATE_IDLE);
}

void GameManager::EraseSelectBoard(Piece * currentSelecetPiece)
{
	BlockManager::GetInstance()->EraseSelectBoard(currentSelecetPiece->GetPieceColor(), currentSelecetPiece->GetPieceType(), currentSelecetPiece->GetPoint());
}


GameManager::~GameManager()
{
	delete m_PlayerBlack;
	delete m_PlayerWhite;
	delete m_BoardManager;
}
