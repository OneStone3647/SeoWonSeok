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
			// ������ �ǽ��� ����Ʈ�� ���
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� ���� ������ �� �ִ� ��ǥ�� ���
			if (m_PlayerBlack->GetSelectPiece()->GetPieceType() == PIECETYPE_KNIGHT)
			{
				if (!m_PlayerBlack->CheckPieceInPoint(m_PlayerBlack->GetMousePoint()) && m_PlayerBlack->GetSelectPiece()->Move(m_PlayerBlack->GetMousePointInBoard()))
				{
					// ������ ������ �Է��Ѵ�.
					m_BoardManager->MovePieceInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard(), BOARDINFO_BLACK);

					BlockManager::GetInstance()->ErasePiece(m_PlayerBlack->GetSelectPiece()->GetPoint());

					m_PlayerBlack->GetSelectPiece()->SetPoint(m_PlayerBlack->GetMousePointInBoard());
					m_PlayerBlack->GetSelectPiece()->SetRect();

					BlockManager::GetInstance()->DrawPiece(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetMousePointInBoard());

					m_PlayerBlack->SetState(STATE_IDLE);
				}
				// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
				else
				{
					BlockManager::GetInstance()->EraseSelectBoard(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetSelectPiece()->GetPoint());
				}
				m_PlayerBlack->SetSelectPiece(NULL);
			}
			else
			{
				// �̵��ϴ� ��ǥ�� ��ֹ��� ���� ������ �� �ִ� ��ǥ�� ���
				if (m_BoardManager->CheckMoveInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard()) && m_PlayerBlack->GetSelectPiece()->Move(m_PlayerBlack->GetMousePointInBoard()))
				{
					// ������ ������ �Է��Ѵ�.
					m_BoardManager->MovePieceInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard(), BOARDINFO_BLACK);

					BlockManager::GetInstance()->ErasePiece(m_PlayerBlack->GetSelectPiece()->GetPoint());

					m_PlayerBlack->GetSelectPiece()->SetPoint(m_PlayerBlack->GetMousePointInBoard());
					m_PlayerBlack->GetSelectPiece()->SetRect();

					BlockManager::GetInstance()->DrawPiece(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetMousePointInBoard());

					m_PlayerBlack->SetState(STATE_IDLE);
				}
				// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
				else
				{
					BlockManager::GetInstance()->EraseSelectBoard(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetSelectPiece()->GetPoint());
				}
				m_PlayerBlack->SetSelectPiece(NULL);
			}
		}
		if (m_PlayerBlack->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_WHITE;
		}
		break;
	case TURN_WHITE:
		m_PlayerWhite->Input(lParam);
		// ������ �ǽ��� ���� ���
		if (m_PlayerWhite->GetSelectPiece() == NULL)
		{
			// ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����Ѵ�.
			if (m_PlayerWhite->SelectPieceInPoint(m_PlayerWhite->GetMousePoint()))
			{
				BlockManager::GetInstance()->DrawSelectBoard(m_PlayerWhite->GetSelectPiece()->GetPoint());
			}
		}
		// ������ �ǽ��� ���� ���
		else
		{
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� ���� ������ �� �ִ� ��ǥ�� ���
			if (!m_PlayerWhite->CheckPieceInPoint(m_PlayerWhite->GetMousePoint()) && m_PlayerWhite->GetSelectPiece()->Move(m_PlayerWhite->GetMousePointInBoard()))
			{
				// ������ ������ �Է��Ѵ�.
				m_BoardManager->MovePieceInBoard(m_PlayerWhite->GetSelectPiece()->GetPoint(), m_PlayerWhite->GetMousePointInBoard(), BOARDINFO_WHITE);

				BlockManager::GetInstance()->ErasePiece(m_PlayerWhite->GetSelectPiece()->GetPoint());

				m_PlayerWhite->GetSelectPiece()->SetPoint(m_PlayerWhite->GetMousePointInBoard());
				m_PlayerWhite->GetSelectPiece()->SetRect();

				BlockManager::GetInstance()->DrawPiece(m_PlayerWhite->GetSelectPiece()->GetPieceColor(), m_PlayerWhite->GetSelectPiece()->GetPieceType(), m_PlayerWhite->GetMousePointInBoard());

				m_PlayerWhite->SetState(STATE_IDLE);
			}
			// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
			else
			{
				BlockManager::GetInstance()->EraseSelectBoard(m_PlayerWhite->GetSelectPiece()->GetPieceColor(), m_PlayerWhite->GetSelectPiece()->GetPieceType(), m_PlayerWhite->GetSelectPiece()->GetPoint());
			}
			m_PlayerWhite->SetSelectPiece(NULL);
		}
		if (m_PlayerWhite->GetState() == STATE_IDLE)
		{
			m_Turn = TURN_BLACK;
		}
		break;
	}
}

void GameManager::Inputt(LPARAM lParam)
{
	// �Ͽ� ���� ���� �Է��ϴ� �÷��̾ ��ȯ�Ѵ�.
	Player* CurrentPlayer = NULL;
	BOARDINFO boardInfo;
	if (m_Turn == TURN_BLACK)
	{
		CurrentPlayer = m_PlayerBlack;
		boardInfo = BOARDINFO_BLACK;
	}
	else
	{
		CurrentPlayer = m_PlayerWhite;
		boardInfo = BOARDINFO_WHITE;
	}

	CurrentPlayer->Input(lParam);
	// ������ �ǽ��� ���� ���
	if (CurrentPlayer->GetSelectPiece() == NULL)
	{
		// ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����Ѵ�.
		if (CurrentPlayer->SelectPieceInPoint(CurrentPlayer->GetMousePoint()))
		{
			BlockManager::GetInstance()->DrawSelectBoard(CurrentPlayer->GetSelectPiece()->GetPoint());
		}
	}
	// ������ �ǽ��� ���� ���
	else
	{
		// �̵��ϴ� ��ǥ�� �ڽ��� ���� ���� ������ �� �ִ� ��ǥ�� ���
		if (!CurrentPlayer->CheckPieceInPoint(CurrentPlayer->GetMousePoint()) && CurrentPlayer->GetSelectPiece()->Move(CurrentPlayer->GetMousePointInBoard()))
		{
			// ������ ������ �Է��Ѵ�.
			m_BoardManager->MovePieceInBoard(CurrentPlayer->GetSelectPiece()->GetPoint(), CurrentPlayer->GetMousePointInBoard(), boardInfo);

			BlockManager::GetInstance()->ErasePiece(CurrentPlayer->GetSelectPiece()->GetPoint());

			CurrentPlayer->GetSelectPiece()->SetPoint(CurrentPlayer->GetMousePointInBoard());
			CurrentPlayer->GetSelectPiece()->SetRect();

			BlockManager::GetInstance()->DrawPiece(CurrentPlayer->GetSelectPiece()->GetPieceColor(), CurrentPlayer->GetSelectPiece()->GetPieceType(), CurrentPlayer->GetMousePointInBoard());

			CurrentPlayer->SetState(STATE_IDLE);
		}
		// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų� ������ �� ���� ��ǥ�� ��� ������ ���� �ʱ�ȭ �Ѵ�.
		else
		{
			BlockManager::GetInstance()->EraseSelectBoard(CurrentPlayer->GetSelectPiece()->GetPieceColor(), CurrentPlayer->GetSelectPiece()->GetPieceType(), CurrentPlayer->GetSelectPiece()->GetPoint());
		}
		CurrentPlayer->SetSelectPiece(NULL);
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


GameManager::~GameManager()
{
	delete m_PlayerBlack;
	delete m_PlayerWhite;
	delete m_BoardManager;
	BlockManager::GetInstance()->Release();
}
