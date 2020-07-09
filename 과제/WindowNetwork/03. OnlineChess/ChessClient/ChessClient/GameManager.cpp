#include "GameManager.h"



GameManager::GameManager()
{
	m_Board = nullptr;
	m_Player = nullptr;
	m_Enemy = nullptr;
}


GameManager::~GameManager()
{
	Release();
}

void GameManager::Init(HWND hWnd)
{
	m_bIsStart = false; 

	m_hWnd = hWnd;
	// GetDC를 통해 DC를 받습니다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만듭니다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 WINDOWWIDTH, 높이 WINDOWHEIGHT의 크기로 만듭니다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 사용한 DC를 해제합니다.
	ReleaseDC(hWnd, hdc);

	NetManager::GetInstance()->Init(m_hWnd);
	while (true)
	{
		if (NetManager::GetInstance()->GetSetTeam())
		{
			break;
		}
	}

	// Board 클래스가 이미 존재할 경우 할당 해제합니다.
	if (m_Board != nullptr)
	{
		delete m_Board;
	}
	// Board 클래스를 동적 할당합니다.
	m_Board = new Board;
	m_Board->Init(m_MemDC);

	// 접속한 순서에 맞는 플레이어가 소유한 피스의 색을 설정합니다.
	InitPlayers();
}

void GameManager::InitPlayers()
{
	if (NetManager::GetInstance()->GetPieceColorSet() == PIECECOLOR_BLACK)
	{
		// 플레이어가 이미 존재할 경우 할당 해제합니다.
		if (m_Player != nullptr)
		{
			delete m_Player;
		}
		// 플레이어를 동적 할당합니다.
		m_Player = new Player;
		m_Player->Init(m_MemDC, PIECECOLOR_BLACK);

		// 상대방이 이미 존재할 경우 할당 해제합니다.
		if (m_Enemy != nullptr)
		{
			delete m_Enemy;
		}
		// 상대방을 동적 할당합니다.
		m_Enemy = new Player;
		m_Enemy->Init(m_MemDC, PIECECOLOR_WHITE);
	}
	else if (NetManager::GetInstance()->GetPieceColorSet() == PIECECOLOR_WHITE)
	{
		// 플레이어가 이미 존재할 경우 할당 해제합니다.
		if (m_Player != nullptr)
		{
			delete m_Player;
		}
		// 플레이어를 동적 할당합니다.
		m_Player = new Player;
		m_Player->Init(m_MemDC, PIECECOLOR_WHITE);

		// 상대방이 이미 존재할 경우 할당 해제합니다.
		if (m_Enemy != nullptr)
		{
			delete m_Enemy;
		}
		// 상대방을 동적 할당합니다.
		m_Enemy = new Player;
		m_Enemy->Init(m_MemDC, PIECECOLOR_BLACK);
	}
}

void GameManager::Release()
{
	//NetManager::GetInstance()->DestroyInstance();

	// Board 클래스를 동적 할당 해제합니다.
	if (m_Board != nullptr)
	{
		delete m_Board;
	}

	// 플에이어를 동적 할당 해제합니다.
	if (m_Player != nullptr)
	{
		delete m_Player;
	}

	// 상대방을 동적 할당 해제합니다.
	if (m_Enemy != nullptr)
	{
		delete m_Enemy;
	}

	// m_MemDC에 이전 비트맵을 연결합니다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어진 DC는 DeleteDC로 지워야합니다.
	DeleteDC(m_MemDC);
}

void GameManager::Update(LPARAM lParam)
{
	if (!m_bIsStart)
	{
		DrawAll();
		m_bIsStart = true;
	}

	if (NetManager::GetInstance()->GetTurn())
	{
		if (m_Player->Input(lParam))
		{
			// 선택한 피스가 없을 경우 마우스 포인터의 위치에 해당하는 피스를 선택합니다.
			if (m_Player->GetSelectPiece() == nullptr && m_Player->SelectPiece(m_Player->GetMousePoint()) != false)
			{
				m_Player->DrawSelectBitmap(m_Player->GetSelectPiece()->GetPoint());
			}
			// 선택한 피스가 있을 경우
			else if (m_Player->GetSelectPiece() != nullptr)
			{
				Piece* CurrentSelectPiece = m_Player->GetSelectPiece();
				// 보드에서 사용하는 픽세단위가 아닌 단순하 좌표입니다. ex) (1, 1)
				POINT BoardPoint = m_Player->GetBoardPoint();

				// 선택한 피스가 폰인 경우
				if (CurrentSelectPiece->GetPieceType() == PIECETYPE_PAWN)
				{
					// 이동하는 좌표에 상대방의 피스가 있을 경우
					if (m_Enemy->SearchPieceinPoint(BoardPoint) != nullptr)
					{
						// 다운캐스팅
						Pawn* tmpPawn = dynamic_cast<Pawn*>(CurrentSelectPiece);
						//공격할 수 있는 좌표일 경우
						if (tmpPawn->CanAttack(BoardPoint))
						{
							Move(m_Player, m_Enemy);
						}
						// 공격할 수 없는 좌표일 경우 선택한 피스를 초기화 합니다.
						else
						{
							m_Player->ReleaseSelectPiece();
							// 선택 표시 비트맵을 지우기 위해 다시 그립니다.
							DrawAll();
						}
					}
					else
					{
						// 이동하는 좌표에 자신의 말이 없고
						// 움직일 수 있는 좌표일 경우
						if (m_Player->SearchPiece(m_Player->GetMousePoint()) == nullptr && CurrentSelectPiece->CanMove(BoardPoint))
						{
							Move(m_Player, m_Enemy);
						}
						else
						{
							m_Player->ReleaseSelectPiece();
							DrawAll();
						}
					}
				}
				//선택한 피스가 나이트인 경우
				else if (CurrentSelectPiece->GetPieceType() == PIECETYPE_KNIGHT)
				{
					// 이동하는 좌표에 자신의 말이 없고
					// 움직일 수 있는 좌표일 경우
					if (m_Player->SearchPieceinPoint(BoardPoint) == nullptr && CurrentSelectPiece->CanMove(BoardPoint))
					{
						Move(m_Player, m_Enemy);
					}
					// 이동하는 좌표에 자신의 말이 있거나
					// 움직일 수 없는 좌표일 경우 선택한 피스를 초기화합니다.
					else
					{
						m_Player->ReleaseSelectPiece();
						// 선택 표시 비트맵을 지우기 위해 다시 그립니다.
						DrawAll();
					}
				}
				// 나머지 피스일 경우
				else
				{
					// 이동하는 좌표에 자신의 말이 없고
					// 움직일 수 있는 좌표이며
					// 이동하는 좌표 전까지 장애물이 없는 경우
					if (m_Player->SearchPieceinPoint(BoardPoint) == nullptr && CurrentSelectPiece->CanMove(BoardPoint)
						&& !CheckObstacle(CurrentSelectPiece->GetPoint(), BoardPoint))
					{
						Move(m_Player, m_Enemy);
					}
					// 이동하는 좌표에 자신의 말이 있거나
					// 움직일 수 없는 좌표일 경우 선택한 피스를 초기화합니다.
					else
					{
						m_Player->ReleaseSelectPiece();
						//선택 표시 비트맵을 지우기 위해 다시 그립니다.
						DrawAll();
					}
				}
			}
		}		

		// 승리 여부를 확인합니다.
		if (!m_Enemy->GetKingIsLive())
		{
			Victory(m_Player);
		}
	}
	else
	{
		EnemyUpdate();
	}

	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
	getchar();
}

void GameManager::EnemyUpdate()
{
	if (NetManager::GetInstance()->GetRecvFlag())
	{
		POINT prevPoint = { NetManager::GetInstance()->GetPoint().prev_X, NetManager::GetInstance()->GetPoint().prev_Y };
		POINT curPoint = { NetManager::GetInstance()->GetPoint().cur_X, NetManager::GetInstance()->GetPoint().cur_Y };

		Piece* tmpPiece = m_Enemy->SearchPieceinPoint(prevPoint);
		tmpPiece->SetPoint(curPoint);
		tmpPiece->SetRect();
		
		if (m_Player->SearchPieceinPoint(curPoint) != nullptr)
		{
			m_Player->SearchPieceinPoint(curPoint)->SetLiveFlag(false);
		}

		DrawAll();
		NetManager::GetInstance()->SetRecvFlag(false);
		NetManager::GetInstance()->SetTurn(true);

		// 승리 여부를 확인한다.
		if (!m_Player->GetKingIsLive())
		{
			Victory(m_Enemy);
		}
	}
}

void GameManager::DrawAll()
{
	m_Board->DrawBoard();
	m_Player->DrawAllPiece();
	m_Enemy->DrawAllPiece();
}

void GameManager::Victory(Player * player)
{
	if (player->GetPieceColor() == PIECECOLOR_BLACK)
	{
		if (MessageBox(m_hWnd, TEXT("흑팀의 승리!!\n다시하시겠습니까?"), TEXT("Winner"), MB_YESNO) == IDYES)
		{
			m_bIsStart = false;
			InitPlayers();
		}
		else
		{
			PostQuitMessage(0);
		}
	}
	else if (player->GetPieceColor() == PIECECOLOR_WHITE)
	{
		if (MessageBox(m_hWnd, TEXT("백팀의 승리!!\n다시하시겠습니까?"), TEXT("Winner"), MB_YESNO) == IDYES)
		{
			m_bIsStart = false;
			InitPlayers();
		}
		else
		{
			PostQuitMessage(0);
		}
	}
}

void GameManager::Move(Player * player, Player * enemy)
{
	// 이동하는 좌표에 상대방의 피스가 있을 경우
	if (enemy->SearchPiece(player->GetMousePoint()))
	{
		vector<Piece*> EnemyPieceList = enemy->GetPieceList();
		vector<Piece*>::size_type i = 0;
		for (i; i < EnemyPieceList.size(); ++i)
		{
			if (EnemyPieceList[i]->GetPoint().x == player->GetBoardPoint().x && EnemyPieceList[i]->GetPoint().y == player->GetBoardPoint().y)
			{
				EnemyPieceList[i]->SetLiveFlag(false);
			}
		}
	}

	POINT prevPoint = player->GetSelectPiece()->GetPoint();
	POINT curPoint = player->GetBoardPoint();
	NetManager::GetInstance()->SetPoint(prevPoint.x, prevPoint.y, curPoint.x, curPoint.y);

	player->GetSelectPiece()->SetPoint(player->GetBoardPoint());
	player->GetSelectPiece()->SetRect();
	DrawAll();

	NetManager::GetInstance()->SetInputFlag(true);
}

// 장애물이 있을 경우 true를 반환합니다.
bool GameManager::CheckObstacle(POINT currentPoint, POINT goalPoint)
{
	// 현재 위치와 목표 위치가 같은 경우 true를 반환합니다.
	if (currentPoint.x == goalPoint.x&&currentPoint.y == goalPoint.y)
	{
		return true;
	}

	// 현재 위치와 목표 위치가 한 칸씩 차이가 나는 경우 false를 반환합니다.
	if (currentPoint.x >= goalPoint.x - 1 && currentPoint.x <= goalPoint.x + 1)
	{
		if (currentPoint.y >= goalPoint.y - 1 && currentPoint.y <= goalPoint.y + 1)
		{
			return false;
		}
	}

	// 현재 좌표에서 목표 좌표 전까지
	// 장애물(자신의 피스 또는 상대방의 피스)가 있는지 확인합니다.

	// x좌표가 같을 경우
	if (currentPoint.x == goalPoint.x)
	{
		if (currentPoint.y > goalPoint.y)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; currentPoint.y != goalPoint.y + 1;)
			{
				currentPoint.y--;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
		else
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; currentPoint.y != goalPoint.y - 1;)
			{
				currentPoint.y++;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
	}
	// y좌표가 같을 경우
	else if (currentPoint.y == goalPoint.y)
	{
		if (currentPoint.x > goalPoint.x)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; currentPoint.x != goalPoint.x + 1;)
			{
				currentPoint.x--;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
		else
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; currentPoint.x != goalPoint.x - 1;)
			{
				currentPoint.x++;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
	}
	// x와 y 둘 다 다를 경우
	else
	{
		if (currentPoint.x > goalPoint.x&& currentPoint.y > goalPoint.y)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; !(currentPoint.x == goalPoint.x + 1 && currentPoint.y == goalPoint.y + 1);)
			{
				currentPoint.x--;
				currentPoint.y--;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
		else if (currentPoint.x < goalPoint.x&& currentPoint.y < goalPoint.y)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; !(currentPoint.x == goalPoint.x - 1 && currentPoint.y == goalPoint.y - 1);)
			{
				currentPoint.x++;
				currentPoint.y++;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
		else if (currentPoint.x > goalPoint.x&& currentPoint.y < goalPoint.y)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; !(currentPoint.x == goalPoint.x + 1 && currentPoint.y == goalPoint.y - 1);)
			{
				currentPoint.x--;
				currentPoint.y++;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
		else if (currentPoint.x < goalPoint.x&& currentPoint.y > goalPoint.y)
		{
			// 목표 전까지 이동하는 중 장애물을 만나면 true를 반환합니다.
			for (; !(currentPoint.x == goalPoint.x - 1 && currentPoint.y == goalPoint.y + 1);)
			{
				currentPoint.x++;
				currentPoint.y--;
				if (m_Player->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
				else if (m_Enemy->SearchPieceinPoint(currentPoint) != nullptr)
				{
					return true;
				}
			}

			// 비어 있다면 false를 반환합니다.
			return false;
		}
	}
	
	return true;
}
