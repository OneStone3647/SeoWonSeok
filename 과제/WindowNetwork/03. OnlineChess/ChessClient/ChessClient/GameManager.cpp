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
	// GetDC�� ���� DC�� �޽��ϴ�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� ����ϴ�.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� WINDOWWIDTH, ���� WINDOWHEIGHT�� ũ��� ����ϴ�.
	m_NewBitmap = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� �����մϴ�.
	ReleaseDC(hWnd, hdc);

	NetManager::GetInstance()->Init(m_hWnd);
	while (true)
	{
		if (NetManager::GetInstance()->GetSetTeam())
		{
			break;
		}
	}

	// Board Ŭ������ �̹� ������ ��� �Ҵ� �����մϴ�.
	if (m_Board != nullptr)
	{
		delete m_Board;
	}
	// Board Ŭ������ ���� �Ҵ��մϴ�.
	m_Board = new Board;
	m_Board->Init(m_MemDC);

	// ������ ������ �´� �÷��̾ ������ �ǽ��� ���� �����մϴ�.
	InitPlayers();
}

void GameManager::InitPlayers()
{
	if (NetManager::GetInstance()->GetPieceColorSet() == PIECECOLOR_BLACK)
	{
		// �÷��̾ �̹� ������ ��� �Ҵ� �����մϴ�.
		if (m_Player != nullptr)
		{
			delete m_Player;
		}
		// �÷��̾ ���� �Ҵ��մϴ�.
		m_Player = new Player;
		m_Player->Init(m_MemDC, PIECECOLOR_BLACK);

		// ������ �̹� ������ ��� �Ҵ� �����մϴ�.
		if (m_Enemy != nullptr)
		{
			delete m_Enemy;
		}
		// ������ ���� �Ҵ��մϴ�.
		m_Enemy = new Player;
		m_Enemy->Init(m_MemDC, PIECECOLOR_WHITE);
	}
	else if (NetManager::GetInstance()->GetPieceColorSet() == PIECECOLOR_WHITE)
	{
		// �÷��̾ �̹� ������ ��� �Ҵ� �����մϴ�.
		if (m_Player != nullptr)
		{
			delete m_Player;
		}
		// �÷��̾ ���� �Ҵ��մϴ�.
		m_Player = new Player;
		m_Player->Init(m_MemDC, PIECECOLOR_WHITE);

		// ������ �̹� ������ ��� �Ҵ� �����մϴ�.
		if (m_Enemy != nullptr)
		{
			delete m_Enemy;
		}
		// ������ ���� �Ҵ��մϴ�.
		m_Enemy = new Player;
		m_Enemy->Init(m_MemDC, PIECECOLOR_BLACK);
	}
}

void GameManager::Release()
{
	//NetManager::GetInstance()->DestroyInstance();

	// Board Ŭ������ ���� �Ҵ� �����մϴ�.
	if (m_Board != nullptr)
	{
		delete m_Board;
	}

	// �ÿ��̾ ���� �Ҵ� �����մϴ�.
	if (m_Player != nullptr)
	{
		delete m_Player;
	}

	// ������ ���� �Ҵ� �����մϴ�.
	if (m_Enemy != nullptr)
	{
		delete m_Enemy;
	}

	// m_MemDC�� ���� ��Ʈ���� �����մϴ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ������� DC�� DeleteDC�� �������մϴ�.
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
			// ������ �ǽ��� ���� ��� ���콺 �������� ��ġ�� �ش��ϴ� �ǽ��� �����մϴ�.
			if (m_Player->GetSelectPiece() == nullptr && m_Player->SelectPiece(m_Player->GetMousePoint()) != false)
			{
				m_Player->DrawSelectBitmap(m_Player->GetSelectPiece()->GetPoint());
			}
			// ������ �ǽ��� ���� ���
			else if (m_Player->GetSelectPiece() != nullptr)
			{
				Piece* CurrentSelectPiece = m_Player->GetSelectPiece();
				// ���忡�� ����ϴ� �ȼ������� �ƴ� �ܼ��� ��ǥ�Դϴ�. ex) (1, 1)
				POINT BoardPoint = m_Player->GetBoardPoint();

				// ������ �ǽ��� ���� ���
				if (CurrentSelectPiece->GetPieceType() == PIECETYPE_PAWN)
				{
					// �̵��ϴ� ��ǥ�� ������ �ǽ��� ���� ���
					if (m_Enemy->SearchPieceinPoint(BoardPoint) != nullptr)
					{
						// �ٿ�ĳ����
						Pawn* tmpPawn = dynamic_cast<Pawn*>(CurrentSelectPiece);
						//������ �� �ִ� ��ǥ�� ���
						if (tmpPawn->CanAttack(BoardPoint))
						{
							Move(m_Player, m_Enemy);
						}
						// ������ �� ���� ��ǥ�� ��� ������ �ǽ��� �ʱ�ȭ �մϴ�.
						else
						{
							m_Player->ReleaseSelectPiece();
							// ���� ǥ�� ��Ʈ���� ����� ���� �ٽ� �׸��ϴ�.
							DrawAll();
						}
					}
					else
					{
						// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
						// ������ �� �ִ� ��ǥ�� ���
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
				//������ �ǽ��� ����Ʈ�� ���
				else if (CurrentSelectPiece->GetPieceType() == PIECETYPE_KNIGHT)
				{
					// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
					// ������ �� �ִ� ��ǥ�� ���
					if (m_Player->SearchPieceinPoint(BoardPoint) == nullptr && CurrentSelectPiece->CanMove(BoardPoint))
					{
						Move(m_Player, m_Enemy);
					}
					// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų�
					// ������ �� ���� ��ǥ�� ��� ������ �ǽ��� �ʱ�ȭ�մϴ�.
					else
					{
						m_Player->ReleaseSelectPiece();
						// ���� ǥ�� ��Ʈ���� ����� ���� �ٽ� �׸��ϴ�.
						DrawAll();
					}
				}
				// ������ �ǽ��� ���
				else
				{
					// �̵��ϴ� ��ǥ�� �ڽ��� ���� ����
					// ������ �� �ִ� ��ǥ�̸�
					// �̵��ϴ� ��ǥ ������ ��ֹ��� ���� ���
					if (m_Player->SearchPieceinPoint(BoardPoint) == nullptr && CurrentSelectPiece->CanMove(BoardPoint)
						&& !CheckObstacle(CurrentSelectPiece->GetPoint(), BoardPoint))
					{
						Move(m_Player, m_Enemy);
					}
					// �̵��ϴ� ��ǥ�� �ڽ��� ���� �ְų�
					// ������ �� ���� ��ǥ�� ��� ������ �ǽ��� �ʱ�ȭ�մϴ�.
					else
					{
						m_Player->ReleaseSelectPiece();
						//���� ǥ�� ��Ʈ���� ����� ���� �ٽ� �׸��ϴ�.
						DrawAll();
					}
				}
			}
		}		

		// �¸� ���θ� Ȯ���մϴ�.
		if (!m_Enemy->GetKingIsLive())
		{
			Victory(m_Player);
		}
	}
	else
	{
		EnemyUpdate();
	}

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
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

		// �¸� ���θ� Ȯ���Ѵ�.
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
		if (MessageBox(m_hWnd, TEXT("������ �¸�!!\n�ٽ��Ͻðڽ��ϱ�?"), TEXT("Winner"), MB_YESNO) == IDYES)
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
		if (MessageBox(m_hWnd, TEXT("������ �¸�!!\n�ٽ��Ͻðڽ��ϱ�?"), TEXT("Winner"), MB_YESNO) == IDYES)
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
	// �̵��ϴ� ��ǥ�� ������ �ǽ��� ���� ���
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

// ��ֹ��� ���� ��� true�� ��ȯ�մϴ�.
bool GameManager::CheckObstacle(POINT currentPoint, POINT goalPoint)
{
	// ���� ��ġ�� ��ǥ ��ġ�� ���� ��� true�� ��ȯ�մϴ�.
	if (currentPoint.x == goalPoint.x&&currentPoint.y == goalPoint.y)
	{
		return true;
	}

	// ���� ��ġ�� ��ǥ ��ġ�� �� ĭ�� ���̰� ���� ��� false�� ��ȯ�մϴ�.
	if (currentPoint.x >= goalPoint.x - 1 && currentPoint.x <= goalPoint.x + 1)
	{
		if (currentPoint.y >= goalPoint.y - 1 && currentPoint.y <= goalPoint.y + 1)
		{
			return false;
		}
	}

	// ���� ��ǥ���� ��ǥ ��ǥ ������
	// ��ֹ�(�ڽ��� �ǽ� �Ǵ� ������ �ǽ�)�� �ִ��� Ȯ���մϴ�.

	// x��ǥ�� ���� ���
	if (currentPoint.x == goalPoint.x)
	{
		if (currentPoint.y > goalPoint.y)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
		else
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
	}
	// y��ǥ�� ���� ���
	else if (currentPoint.y == goalPoint.y)
	{
		if (currentPoint.x > goalPoint.x)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
		else
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
	}
	// x�� y �� �� �ٸ� ���
	else
	{
		if (currentPoint.x > goalPoint.x&& currentPoint.y > goalPoint.y)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
		else if (currentPoint.x < goalPoint.x&& currentPoint.y < goalPoint.y)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
		else if (currentPoint.x > goalPoint.x&& currentPoint.y < goalPoint.y)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
		else if (currentPoint.x < goalPoint.x&& currentPoint.y > goalPoint.y)
		{
			// ��ǥ ������ �̵��ϴ� �� ��ֹ��� ������ true�� ��ȯ�մϴ�.
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

			// ��� �ִٸ� false�� ��ȯ�մϴ�.
			return false;
		}
	}
	
	return true;
}
