#include "GameManager.h"



GameManager::GameManager()
{
	m_PlayerBlack = NULL;
	m_PlayerWhite = NULL;
	m_BlockManager = NULL;

	m_Turn = TURN_BLACK;
}

// �ʱ�ȭ
void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_hWnd = hWnd;
	m_hInst = hInst;
	m_bFirstPlay = true;
	// ������ �÷��̾ ���� �����Ѵ�.

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

	if (m_BlockManager != NULL)
	{
		delete m_BlockManager;
	}
	m_BlockManager = new BlockManager;
	m_BlockManager->Init(hWnd, hInst);
	// �� �÷��̾ ���� �ǽ��� �ʱ� ��ġ ������ ���忡 �����Ѵ�.
	m_BlockManager->SetBoardInPieceInit(m_PlayerBlack);
	m_BlockManager->SetBoardInPieceInit(m_PlayerWhite);
}

// �ʱ� ����� �ǽ��� �׸���.
void GameManager::DrawInitBoard()
{
	m_BlockManager->DrawAllBoard();
	m_BlockManager->DrawInitPiece(m_PlayerBlack->GetPieceList());
	m_BlockManager->DrawInitPiece(m_PlayerWhite->GetPieceList());
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

	// ������ �ǽ��� ���� ���
	if (CurrentPlayer->GetSelectPiece() == NULL)
	{
		// ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����Ѵ�.
		if (CurrentPlayer->SelectPieceInPoint(MousePoint))
		{
			Piece* CurrentSelectPiece = CurrentPlayer->GetSelectPiece();							// ���� ���õ� �ǽ�
			m_BlockManager->DrawSelectBoard(CurrentSelectPiece->GetPoint());
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
			if (m_BlockManager->SearchBoardInfoList(MousePointInBoard)->BoardInfo == EnemyBoardInfo)
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
			if (!CurrentPlayer->CheckPieceInPoint(MousePoint) && CurrentSelectPiece->Move(MousePointInBoard) && m_BlockManager->CheckMoveInBoard(CurrentSelectPiece->GetPoint(), MousePointInBoard))
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
				m_Turn = TURN_BLACK;
				Init(m_hWnd, m_hInst);
			}
			else
			{
				PostQuitMessage(0);
			}
		}
		else if (EnemyPlayer->GetPlayerColor() == PLAYERCOLOR_WHITE)
		{
			if (MessageBox(m_hWnd, TEXT("������ �¸�!!\n�ٽ��Ͻðڽ��ϱ�?"), TEXT("Winner"), MB_YESNO) == IDYES)
			{
				m_Turn = TURN_WHITE;
				Init(m_hWnd, m_hInst);
			}
			else
			{
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
	// �̵��ϴ� ��ǥ�� ������ �ǽ��� ���� ���
	if (m_BlockManager->SearchBoardInfoList(mousePointInBoard)->BoardInfo == enemyBoardInfo)
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
		m_BlockManager->SetBoardInfo(mousePointInBoard, BOARDINFO_NONE);
		m_BlockManager->ErasePiece(mousePointInBoard);
	}

	// ������ ������ �Է��Ѵ�.
	m_BlockManager->MovePieceInBoard(currentSelectPiece->GetPoint(), mousePointInBoard, currentBoardInfo);

	// ���� ������ �ǽ� ��Ʈ���� �����.
	m_BlockManager->ErasePiece(currentSelectPiece->GetPoint());

	// ���� ������ �ǽ��� ������ �����Ѵ�.
	currentSelectPiece->SetPoint(mousePointInBoard);
	currentSelectPiece->SetRect();

	// ������ �ǽ��� ������ �������� �ǽ��� �׸���.
	m_BlockManager->DrawPiece(currentSelectPiece->GetPieceColor(), currentSelectPiece->GetPieceType(), mousePointInBoard);

	currentPlayer->SetState(STATE_IDLE);
}

void GameManager::EraseSelectBoard(Piece * currentSelecetPiece)
{
	m_BlockManager->EraseSelectBoard(currentSelecetPiece->GetPieceColor(), currentSelecetPiece->GetPieceType(), currentSelecetPiece->GetPoint());
}


GameManager::~GameManager()
{
	delete m_PlayerBlack;
	delete m_PlayerWhite;
	delete m_BlockManager;
}
