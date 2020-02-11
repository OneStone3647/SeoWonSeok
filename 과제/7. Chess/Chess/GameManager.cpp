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
			// 선택한 피스가 나이트인 경우
			// 이동하는 좌표에 자신의 말이 없고 움직일 수 있는 좌표일 경우
			if (m_PlayerBlack->GetSelectPiece()->GetPieceType() == PIECETYPE_KNIGHT)
			{
				if (!m_PlayerBlack->CheckPieceInPoint(m_PlayerBlack->GetMousePoint()) && m_PlayerBlack->GetSelectPiece()->Move(m_PlayerBlack->GetMousePointInBoard()))
				{
					// 보드의 정보를 입력한다.
					m_BoardManager->MovePieceInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard(), BOARDINFO_BLACK);

					BlockManager::GetInstance()->ErasePiece(m_PlayerBlack->GetSelectPiece()->GetPoint());

					m_PlayerBlack->GetSelectPiece()->SetPoint(m_PlayerBlack->GetMousePointInBoard());
					m_PlayerBlack->GetSelectPiece()->SetRect();

					BlockManager::GetInstance()->DrawPiece(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetMousePointInBoard());

					m_PlayerBlack->SetState(STATE_IDLE);
				}
				// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
				else
				{
					BlockManager::GetInstance()->EraseSelectBoard(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetSelectPiece()->GetPoint());
				}
				m_PlayerBlack->SetSelectPiece(NULL);
			}
			else
			{
				// 이동하는 좌표에 장애물이 없고 움직일 수 있는 좌표일 경우
				if (m_BoardManager->CheckMoveInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard()) && m_PlayerBlack->GetSelectPiece()->Move(m_PlayerBlack->GetMousePointInBoard()))
				{
					// 보드의 정보를 입력한다.
					m_BoardManager->MovePieceInBoard(m_PlayerBlack->GetSelectPiece()->GetPoint(), m_PlayerBlack->GetMousePointInBoard(), BOARDINFO_BLACK);

					BlockManager::GetInstance()->ErasePiece(m_PlayerBlack->GetSelectPiece()->GetPoint());

					m_PlayerBlack->GetSelectPiece()->SetPoint(m_PlayerBlack->GetMousePointInBoard());
					m_PlayerBlack->GetSelectPiece()->SetRect();

					BlockManager::GetInstance()->DrawPiece(m_PlayerBlack->GetSelectPiece()->GetPieceColor(), m_PlayerBlack->GetSelectPiece()->GetPieceType(), m_PlayerBlack->GetMousePointInBoard());

					m_PlayerBlack->SetState(STATE_IDLE);
				}
				// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
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
		// 선택한 피스가 없을 경우
		if (m_PlayerWhite->GetSelectPiece() == NULL)
		{
			// 마우스 포인터의 위치에 해당하는 피스를 선택한다.
			if (m_PlayerWhite->SelectPieceInPoint(m_PlayerWhite->GetMousePoint()))
			{
				BlockManager::GetInstance()->DrawSelectBoard(m_PlayerWhite->GetSelectPiece()->GetPoint());
			}
		}
		// 선택한 피스가 있을 경우
		else
		{
			// 이동하는 좌표에 자신의 말이 없고 움직일 수 있는 좌표일 경우
			if (!m_PlayerWhite->CheckPieceInPoint(m_PlayerWhite->GetMousePoint()) && m_PlayerWhite->GetSelectPiece()->Move(m_PlayerWhite->GetMousePointInBoard()))
			{
				// 보드의 정보를 입력한다.
				m_BoardManager->MovePieceInBoard(m_PlayerWhite->GetSelectPiece()->GetPoint(), m_PlayerWhite->GetMousePointInBoard(), BOARDINFO_WHITE);

				BlockManager::GetInstance()->ErasePiece(m_PlayerWhite->GetSelectPiece()->GetPoint());

				m_PlayerWhite->GetSelectPiece()->SetPoint(m_PlayerWhite->GetMousePointInBoard());
				m_PlayerWhite->GetSelectPiece()->SetRect();

				BlockManager::GetInstance()->DrawPiece(m_PlayerWhite->GetSelectPiece()->GetPieceColor(), m_PlayerWhite->GetSelectPiece()->GetPieceType(), m_PlayerWhite->GetMousePointInBoard());

				m_PlayerWhite->SetState(STATE_IDLE);
			}
			// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
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
	// 턴에 따라 현재 입력하는 플레이어를 전환한다.
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
	// 선택한 피스가 없을 경우
	if (CurrentPlayer->GetSelectPiece() == NULL)
	{
		// 마우스 포인터의 위치에 해당하는 피스를 선택한다.
		if (CurrentPlayer->SelectPieceInPoint(CurrentPlayer->GetMousePoint()))
		{
			BlockManager::GetInstance()->DrawSelectBoard(CurrentPlayer->GetSelectPiece()->GetPoint());
		}
	}
	// 선택한 피스가 있을 경우
	else
	{
		// 이동하는 좌표에 자신의 말이 없고 움직일 수 있는 좌표일 경우
		if (!CurrentPlayer->CheckPieceInPoint(CurrentPlayer->GetMousePoint()) && CurrentPlayer->GetSelectPiece()->Move(CurrentPlayer->GetMousePointInBoard()))
		{
			// 보드의 정보를 입력한다.
			m_BoardManager->MovePieceInBoard(CurrentPlayer->GetSelectPiece()->GetPoint(), CurrentPlayer->GetMousePointInBoard(), boardInfo);

			BlockManager::GetInstance()->ErasePiece(CurrentPlayer->GetSelectPiece()->GetPoint());

			CurrentPlayer->GetSelectPiece()->SetPoint(CurrentPlayer->GetMousePointInBoard());
			CurrentPlayer->GetSelectPiece()->SetRect();

			BlockManager::GetInstance()->DrawPiece(CurrentPlayer->GetSelectPiece()->GetPieceColor(), CurrentPlayer->GetSelectPiece()->GetPieceType(), CurrentPlayer->GetMousePointInBoard());

			CurrentPlayer->SetState(STATE_IDLE);
		}
		// 이동하는 좌표에 자신의 말이 있거나 움직일 수 없는 좌표일 경우 선택한 말을 초기화 한다.
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
