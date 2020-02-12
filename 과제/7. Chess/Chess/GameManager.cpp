#include "GameManager.h"



GameManager::GameManager()
{
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
	m_BoardManager = NULL;
}

// �ʱ�ȭ
void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_hWnd = hWnd;
	m_hInst = hInst;
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

	if (m_BoardManager != NULL)
	{
		delete m_BoardManager;
	}
	m_BoardManager = new BoardManager;
	m_BoardManager->Init();
	// �� �÷��̾ ���� �ǽ��� �ʱ� ��ġ ������ ���忡 �����Ѵ�.
	m_BoardManager->SetBoardInPieceInit(m_PlayerBlack);
	m_BoardManager->SetBoardInPieceInit(m_PlayerWhite);
}

// �ʱ� ����� �ǽ��� �׸���.
void GameManager::DrawInitBoard()
{
	BlockManager::GetInstance()->DrawAllBoard();
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerBlack->GetPieceList());
	BlockManager::GetInstance()->DrawInitPiece(m_PlayerWhite->GetPieceList());
	m_bFirstPlay = false;
}

void GameManager::Input(LPARAM lParam)
{
	// �Ͽ� ���� ���� �Է��ϴ� �÷��̾ ��ȯ�Ѵ�.
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

	POINT MousePoint = CurrentPlayer->GetMousePoint();								// �ȼ��� �� ���콺�� ������ ex) (125, 250)
	POINT MousePointInBoard = CurrentPlayer->GetMousePointInBoard();			// ���忡 ����ϴ� ���콺�� ������ ex) (8, 4)
	Board** tmpBoard = m_BoardManager->GetBoard();

	// ������ �ǽ��� ���� ���
	if (CurrentPlayer->GetSelectPiece() == NULL)
	{
		// ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����Ѵ�.
		if (CurrentPlayer->SelectPieceInPoint(MousePoint))
		{
			Piece* CurrentSelectPiece = CurrentPlayer->GetSelectPiece();							// ���� ���õ� �ǽ�
			BlockManager::GetInstance()->DrawSelectBoard(CurrentSelectPiece->GetPoint());
		}
	}
	// ������ �ǽ��� ���� ���
	else
	{
		Piece* CurrentSelectPiece = CurrentPlayer->GetSelectPiece();							// ���� ���õ� �ǽ�
		// ������ �ǽ��� ����Ʈ�� ���
		if (CurrentSelectPiece->GetPieceType() == PIECETYPE_KNIGHT)
		{
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
			// ������ �� �ִ� ��ǥ�� ���
			if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard))
			{
				Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
			}
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų�
			// ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
			else
			{
				EraseSelectBoard(CurrentSelectPiece);
			}
			CurrentPlayer->SetSelectPiece(NULL);
		}
		// ������ �ǽ��� ���� ���
		else if (CurrentSelectPiece->GetPieceType() == PIECETYPE_PAWN)
		{
			if (tmpBoard[MousePointInBoard.x][MousePointInBoard.y].GetBoardInfo() == EnemyBoardInfo)
			{
				// �ٿ�ĳ����
				Pawn* tmpPawn = dynamic_cast<Pawn*>(CurrentSelectPiece);
				// �����ϴ� ��ǥ�� �ڽ��� ���� ����
				// ������ �� �ִ� ��ǥ�� ���
				if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && tmpPawn->Attack(MousePointInBoard))
				{
					Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
				}
				// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų�
				// ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
				else
				{
					EraseSelectBoard(CurrentSelectPiece);
				}
				CurrentPlayer->SetSelectPiece(NULL);
			}
			else
			{
				// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
				// ������ �� �ִ� ��ǥ�� ���
				if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard))
				{
					Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
				}
				// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų�
				// ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
				else
				{
					EraseSelectBoard(CurrentSelectPiece);
				}
				CurrentPlayer->SetSelectPiece(NULL);
			}
		}
		else
		{
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
			// ������ �� �ִ� ��ǥ�̸�
			// �̵��ϴ� ��ǥ ������ ��ֹ��� ���� ���
			if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard) && m_BoardManager->CheckMoveInBoard(CurrentSelectPiece->GetPoint(), MousePointInBoard))
			{
				Move(CurrentPlayer, EnemyPlayer, CurrentSelectPiece, MousePoint, MousePointInBoard, CurrentBoardInfo, EnemyBoardInfo);
			}
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
			else
			{
				EraseSelectBoard(CurrentSelectPiece);
			}
			CurrentPlayer->SetSelectPiece(NULL);
		}
	}

	// ŷ�� 15���� ����Ǿ��ִ�.
	// ŷ�� �׾��� ��� ��� â�� ��Ÿ����.
	if (!EnemyPlayer->GetPieceList()[15]->GetLiveFlag())
	{
		if (EnemyPlayer->GetPlayerColor() == PLAYERCOLOR_BLACK)
		{
			if (MessageBox(m_hWnd, TEXT("������ �¸�!!\n�ٽ��Ͻðڽ��ϱ�?"), TEXT("Winner"), MB_YESNO) == IDYES)
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
			if (MessageBox(m_hWnd, TEXT("������ �¸�!!\n�ٽ��Ͻðڽ��ϱ�?"), TEXT("Winner"), MB_YESNO) == IDYES)
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

	// �̵��ϴ� ��ǥ�� ������ �ǽ��� ���� ���
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

	// ������ ������ �Է��Ѵ�.
	m_BoardManager->MovePieceInBoard(currentSelectPiece->GetPoint(), mousePointInBoard, currentBoardInfo);

	// ���� ������ �ǽ� ��Ʈ���� �����.
	BlockManager::GetInstance()->ErasePiece(currentSelectPiece->GetPoint());

	// ���� ������ �ǽ��� ������ �����Ѵ�.
	currentSelectPiece->SetPoint(mousePointInBoard);
	currentSelectPiece->SetRect();

	// ������ �ǽ��� ������ �������� �ǽ��� �׸���.
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
