#include "GameManager.h"
#include "DrawManager.h"
#include "NetManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	Release();
}

void GameManager::Init()
{
	m_Turn = 1;

	m_bIsPlay = true;

	if (NetManager::GetInstance()->GetPlayerSet() == PLAYER1)
	{
		if (m_Player != NULL)
		{
			delete m_Player;
		}
		m_Player = new Player;
		m_Player->Init(PLAYER1);

		if (m_Enemy != NULL)
		{
			delete m_Enemy;
		}
		m_Enemy = new Player;
		m_Enemy->Init(PLAYER2);
	}
	else if (NetManager::GetInstance()->GetPlayerSet() == PLAYER2)
	{
		if (m_Player != NULL)
		{
			delete m_Player;
		}
		m_Player = new Player;
		m_Player->Init(PLAYER2);

		if (m_Enemy != NULL)
		{
			delete m_Enemy;
		}
		m_Enemy = new Player;
		m_Enemy->Init(PLAYER1);
	}
}

void GameManager::Reset()
{
	m_Player->Init();
	m_Enemy->Init();
	m_Turn = 1;

	DrawManager::GetInstance()->DrawMap(MAPWIDTH, MAPHEIGHT);
	//string 	tmpMain = "Turn : ";
	//string tmpSub = to_string(m_Turn);
	//tmpMain += tmpSub;
	//DrawManager::GetInstance()->DrawMidText(tmpMain, MAPWIDTH, MAPHEIGHT + 4);
	
	//DrawManager::GetInstance()->ErasePoint(MAPWIDTH + 5, MAPHEIGHT + 4);
	DrawManager::GetInstance()->TextDraw("  ", MAPWIDTH + 4, MAPHEIGHT + 4);

	DrawInfo(m_Player);
}

void GameManager::Release()
{
	if (m_Player != NULL)
	{
		delete m_Player;
	}

	if (m_Enemy != NULL)
	{
		delete m_Enemy;
	}
	m_Enemy = new Player;
}

void GameManager::Update()
{
	DrawManager::GetInstance()->DrawMap(MAPWIDTH, MAPHEIGHT);
	DrawInfo(m_Player);
	while (m_bIsPlay)
	{
		if (NetManager::GetInstance()->GetMyTurn())
		{
			Input();
		}
		else
		{
			EnemyUpdate();
		}
	}
}

void GameManager::Input()
{
	char key;
	while (NetManager::GetInstance()->GetMyTurn())
	{
		DrawAllStone();
		DrawInfo(m_Player);
		DrawPlayer(m_Player);
		key = getch();
		ErasePlayer(m_Player);
		switch (key)
		{
		case DIRECTION_UP:
			if (m_Player->GetY() > 0)
			{
				m_Player->PlusY(-1);
			}
			break;
		case DIRECTION_LEFT:
			if (m_Player->GetX() * 2 > 0)
			{
				m_Player->PlusX(-1);
			}
			break;
		case DIRECTION_DOWN:
			if (m_Player->GetY() < MAPHEIGHT - 1)
			{
				m_Player->PlusY(1);
			}
			break;
		case DIRECTION_RIGHT:
			if (m_Player->GetX() * 2 < MAPWIDTH * 2 - 3)
			{
				m_Player->PlusX(1);
			}
			break;
		case PUT:
			if (!CheckStone(m_Player->GetX(), m_Player->GetY()))
			{
				m_Turn++;
				NetManager::GetInstance()->SetPointX(m_Player->GetX());
				NetManager::GetInstance()->SetPointY(m_Player->GetY());
				m_Player->PutStone();
				DrawManager::GetInstance()->DrawPoint(m_Player->GetStoneShape(), m_Player->GetX(), m_Player->GetY());
				NetManager::GetInstance()->SetInputFlag(true);
				NetManager::GetInstance()->SetMyTurn(false);
				if (m_Player->GetStoneSize() > 4 && m_Player->CheckVictory())
				{
					DrawVictory(m_Player);
					Reset();
				}
			}
			break;
		case ESC:
			return;
		}
	}
}

void GameManager::EnemyUpdate()
{
	if (NetManager::GetInstance()->GetRecvFlag())
	{
		m_Turn++;
		m_Enemy->SetXY(NetManager::GetInstance()->GetPoint().X, NetManager::GetInstance()->GetPoint().Y);

		m_Enemy->PutStone();
		DrawManager::GetInstance()->DrawPoint(m_Enemy->GetStoneShape(), m_Enemy->GetX(), m_Enemy->GetY());
		NetManager::GetInstance()->SetRecvFlag(false);
		NetManager::GetInstance()->SetMyTurn(true);
		if (m_Enemy->GetStoneSize() > 4 && m_Enemy->CheckVictory())
		{
			DrawVictory(m_Enemy);
			Reset();
		}
	}
}

void GameManager::DrawInfo(Player * player)
{
	DrawManager::GetInstance()->DrawMidText("====조작키====", MAPWIDTH, MAPHEIGHT);
	DrawManager::GetInstance()->DrawMidText("이동 : A,S,W,D 돌놓기 : ENTER", MAPWIDTH, MAPHEIGHT + 1);
	DrawManager::GetInstance()->DrawMidText("종료 : ESC", MAPWIDTH, MAPHEIGHT + 2);

	string tmpMain;
	string tmpSub;
	tmpMain = "Player Name : ";
	tmpMain += player->GetPlayerName();
	tmpMain += tmpSub;
	DrawManager::GetInstance()->DrawMidText(tmpMain, MAPWIDTH, MAPHEIGHT + 3);

	tmpMain = "Turn : ";
	tmpSub = to_string(m_Turn);
	tmpMain += tmpSub;
	DrawManager::GetInstance()->DrawMidText(tmpMain, MAPWIDTH, MAPHEIGHT + 4);
}

void GameManager::DrawAllStone()
{
	vector<Stone*> playerStone = m_Player->GetAllStone();
	for (auto iter = playerStone.begin(); iter != playerStone.end(); ++iter)
	{
		DrawManager::GetInstance()->DrawPoint(m_Player->GetStoneShape(), (*iter)->GetX(), (*iter)->GetY());
	}


	vector<Stone*> enemyStone = m_Enemy->GetAllStone();
	for (auto iter = enemyStone.begin(); iter != enemyStone.end(); ++iter)
	{
		DrawManager::GetInstance()->DrawPoint(m_Enemy->GetStoneShape(), (*iter)->GetX(), (*iter)->GetY());
	}
}

// 찾는 포인트에 돌이 있으면 그리고 true를 반환한다.
// 커서가 돌의 위를 지나갈 때 사용한다.
bool GameManager::CheckStone(int x, int y)
{
	if (m_Player->SearchStone(x, y))
	{
		DrawManager::GetInstance()->DrawPoint(m_Player->GetStoneShape(), m_Player->GetX(), m_Player->GetY());
		return true;
	}
	if (m_Enemy->SearchStone(x, y))
	{
		DrawManager::GetInstance()->DrawPoint(m_Enemy->GetStoneShape(), m_Enemy->GetX(), m_Enemy->GetY());
		return true;
	}

	return false;
}

void GameManager::DrawPlayer(Player * player)
{
	DrawManager::GetInstance()->DrawPoint(player->GetStoneShape(), player->GetX(), player->GetY());
}

void GameManager::ErasePlayer(Player * player)
{
	DrawManager::GetInstance()->ErasePoint(player->GetX(), player->GetY());
	if (!CheckStone(player->GetX(), player->GetY()))
	{
		DrawManager::GetInstance()->ReDrawPoint(player->GetX(), player->GetY(), MAPWIDTH, MAPHEIGHT);
	}
}

void GameManager::DrawVictory(Player * player)
{
	if (player->GetTeam() == PLAYER1)
	{
		DrawManager::GetInstance()->DrawMidText("Player1 승리!!", MAPWIDTH, MAPHEIGHT / 2);
	}

	if (player->GetTeam() == PLAYER2)
	{
		DrawManager::GetInstance()->DrawMidText("Player2 승리!!", MAPWIDTH, MAPHEIGHT / 2);
	}

	system("pause");
}
