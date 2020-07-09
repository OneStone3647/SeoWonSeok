#include "FightGame.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"



FightGame::FightGame()
{
}


FightGame::~FightGame()
{
}

void FightGame::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);

	m_BackBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameBack.bmp");

	m_TimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperTimeBar.bmp");
	m_TimeBar->SetAnchor(JEngine::ANCHOR_CENTER);

	m_TimeOverBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\TimeOver.bmp");
	m_TimeOverBitmap->SetAnchor(JEngine::ANCHOR_CENTER);

	m_FeverBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\Fever1.bmp");
	m_FeverBar->SetAnchor(JEngine::ANCHOR_CENTER);

	m_FeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FeverEffect3.bmp");

	m_Deffence = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FeverEffect.bmp");
	m_Deffence->SetAnchor(JEngine::ANCHOR_CENTER);

	m_Score = 0;
	m_bIsFever = false;
	m_FeverStack = 0;

	m_Flight.Init();

	m_ElapseTime = 0;
	m_Time = 0;
	m_bIsTimeOver = false;

	m_ExitTime = 0;

	m_Field = { 4, 100, 410, 600 };

	if (!m_Bullet.empty())
	{
		for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		vector<Bullet*>().swap(m_Bullet);
	}

	if (!m_Star.empty())
	{
		for (auto iter = m_Star.begin(); iter != m_Star.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		vector<FlightStar*>().swap(m_Star);
	}

	m_SpawnTime = 1000.0f;
	m_StartSpawnTimer = 0.0f;
	m_CurSpawnTimer = 0.0f;

	m_bHasDef = false;
	m_DefTime = 1000.0f;
	m_StartDefTimer = 0.0f;
	m_CurDefTimer = 0.0f;
}

bool FightGame::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAMESELECT);
	}
	else
	{
		if (!m_Flight.GetHit() && !m_bIsTimeOver)
		{
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_UP) && (m_Flight.GetY() - m_Flight.GetBitmap()->GetHeight() / 2 > m_Field.top))
			{
				m_Flight.Move(0, -fETime);
			}
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_DOWN) && (m_Flight.GetY() + m_Flight.GetBitmap()->GetHeight() / 2 < m_Field.bottom))
			{
				m_Flight.Move(0, fETime);
			}
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_RIGHT) && (m_Flight.GetX() + m_Flight.GetBitmap()->GetWidth() / 2 < m_Field.right))
			{
				m_Flight.Move(fETime, 0);

			}
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_LEFT) && (m_Flight.GetX() - m_Flight.GetBitmap()->GetWidth() / 2 > m_Field.left))
			{
				m_Flight.Move(-fETime, 0);
			}
		}
	}

	return false;
}

void FightGame::Update(float fETime)
{
	if (fETime)
	{
		m_ElapseTime++;
		m_Time = m_ElapseTime / 100;
	}

	if (m_Time > 19)
	{
		m_bIsTimeOver = true;
		if (m_bIsTimeOver && m_Time > 21)
		{
			SaveScore();
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAMESELECT);
		}
	}

	if (m_ElapseTime % 18 == 0)
	{
		SpawnStar();
	}

	for (vector<FlightStar*>::size_type i = 0; i < m_Star.size(); ++i)
	{
		m_Star[i]->Update(fETime);
		if (m_Star[i]->GetSpawn())
		{
			if (m_Star[i]->GetCollision().isCollision(m_Flight.GetCollision()) && !m_Flight.GetHit() && !m_bHasDef)
			{
				m_Star[i]->SetSpawn(false);
				m_Score += m_Star[i]->GetScore();
				JEngine::UIManager::GetInstance()->RelaaseUI();

				if (!m_bIsFever)
				{
					m_FeverStack++;
				}
				if (m_FeverStack >= 10)
				{
					m_bIsFever = true;
				}
			}
			if (!m_Star[i]->GetCollision().isCollision(m_Field))
			{
				m_Star[i]->SetSpawn(false);
			}
		}
	}

	if (m_ElapseTime % 12 == 0)
	{
		SpawnBullet();
	}

	for (vector<Bullet*>::size_type i = 0; i < m_Bullet.size(); ++i)
	{
		m_Bullet[i]->Update(fETime);
		if (m_Bullet[i]->GetSpawn())
		{
			if (m_Bullet[i]->GetCollision().isCollision(m_Flight.GetCollision()) && !m_Flight.GetHit() && !m_bHasDef)
			{
				m_Bullet[i]->SetSpawn(false);
				m_Flight.SetHit(true);

				if (m_bIsFever)
				{
					m_FeverStack = 0;
					m_bIsFever = false;
				}

				if (m_FeverStack > 0)
				{
					m_FeverStack--;
				}
				m_ElapseTime += 100;

				m_StartSpawnTimer = GetTickCount();
			}

			if (!m_Bullet[i]->GetCollision().isCollision(m_Field))
			{
				m_Bullet[i]->SetSpawn(false);
			}
		}
	}

	if (m_Flight.GetHit())
	{
		m_CurSpawnTimer = GetTickCount();
		if (m_CurSpawnTimer - m_StartSpawnTimer >= m_SpawnTime)
		{
			m_Flight.SetHit(false);
			m_StartSpawnTimer = m_CurSpawnTimer;

			m_bHasDef = true;
			m_StartDefTimer = GetTickCount();
		}
	}

	m_CurDefTimer = GetTickCount();
	if (m_CurDefTimer - m_StartDefTimer >= m_DefTime)
	{
		m_bHasDef = false;
		m_StartDefTimer = m_CurDefTimer;
	}
}

void FightGame::Draw(HDC hdc)
{
	m_BackBitmap->DrawBitblt(0, 0);
	DrawTimeBar();
	DrawFeverBar();
	DrawScore();
	m_Flight.Draw();

	if (m_bHasDef)
	{
		m_Deffence->Draw(m_Flight.GetX(), m_Flight.GetY());
	}

	if (m_bIsFever)
	{
		m_FeverEffect->Draw(0, 0);
	}

	for (vector<FlightStar*>::size_type i = 0; i < m_Star.size(); ++i)
	{
		m_Star[i]->Draw();
	}

	for (vector<Bullet*>::size_type i = 0; i < m_Bullet.size(); ++i)
	{
		m_Bullet[i]->Draw();
	}

	if (m_bIsTimeOver)
	{
		m_TimeOverBitmap->Draw(WindowX / 2, WindowY / 2);
	}

	//Rectangle(JEngine::ResoucesManager::GetInstance()->GetBackDC(), m_Field.left, m_Field.top, m_Field.right, m_Field.bottom);
}

void FightGame::Release()
{
	JEngine::UIManager::GetInstance()->RelaaseUI();

	for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	vector<Bullet*>().swap(m_Bullet);

	for (auto iter = m_Star.begin(); iter != m_Star.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	vector<FlightStar*>().swap(m_Star);
}

void FightGame::DrawScore()
{
	JEngine::UIManager::GetInstance()->AddLabel(to_string(m_Score), WindowX / 2, 20, DT_CENTER);
}

void FightGame::DrawFeverBar()
{
	float percent = m_FeverStack * 0.1f;

	m_FeverBar->Draw(WindowX / 2, 66, percent);
}

void FightGame::DrawTimeBar()
{
	float percent = (20 - m_Time) * 0.05f;

	m_TimeBar->Draw(WindowX / 2, WindowY - 14, percent);
}

void FightGame::SaveScore()
{
	int LoadScore = 0;
	HANDLE hFile = CreateFile(TEXT("FightGameScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &LoadScore, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}

	if (m_Score > LoadScore)
	{
		hFile = CreateFile(TEXT("FightGameScore.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, &m_Score, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}
}

JEngine::POINT FightGame::GetRandomPoint(FlightObject * target)
{
	int randomX = 0;
	int randomY = 0;
	bool bFlagX = false;
	bool bFlagY = false;

	switch (target->GetDirection())
	{
	case DIRECTION_UP:
	case DIRECTION_RU:
	case DIRECTION_LU:
		{
			while (!bFlagX)
			{
				srand((unsigned int)time(NULL));
				randomX = (GetTickCount() % m_Field.right) + m_Field.left;
				if (randomX > m_Field.left && randomX < m_Field.right)
				{
					bFlagX = true;
				}
			}

			randomY = m_Field.bottom + 2;
		}
		break;
	case DIRECTION_DOWN:
	case DIRECTION_RD:
	case DIRECTION_LD:
		{
			while (!bFlagX)
			{
				srand((unsigned int)time(NULL));
				randomX = (GetTickCount() % m_Field.right) + m_Field.left;
				if (randomX > m_Field.left && randomX < m_Field.right)
				{
					bFlagX = true;
				}
			}

			randomY = m_Field.top - 2;
		}
		break;
	case DIRECTION_RIGHT:
		{
			while (!bFlagY)
			{
				srand((unsigned int)time(NULL));
				randomY = (GetTickCount() % m_Field.bottom) + m_Field.top;
				if (randomY > m_Field.top && randomY < m_Field.bottom)
				{
					bFlagY = true;
				}
			}

			randomX = m_Field.left - 2;
		}
		break;
	case DIRECTION_LEFT:
		{
			while (!bFlagY)
			{
				srand((unsigned int)time(NULL));
				randomY = (GetTickCount() % m_Field.bottom) + m_Field.top;
				if (randomY > m_Field.top && randomY < m_Field.bottom)
				{
					bFlagY = true;
				}
			}

			randomX = m_Field.right + 2;
		}
		break;
	}

	JEngine::POINT tmpPoint(randomX, randomY);
	return tmpPoint;
}

void FightGame::SpawnBullet()
{
	for (vector<Bullet*>::size_type i = 0; i < m_Bullet.size(); ++i)
	{
		if (!m_Bullet[i]->GetSpawn())
		{
			m_Bullet[i]->Init();
			JEngine::POINT tmpPoint = GetRandomPoint(m_Bullet[i]);
			m_Bullet[i]->Spawn(tmpPoint.x, tmpPoint.y);
			return;
		}
	}

	Bullet* newBullet = new Bullet;
	newBullet->Init();
	JEngine::POINT tmpPoint = GetRandomPoint(newBullet);
	newBullet->Spawn(tmpPoint.x, tmpPoint.y);
	m_Bullet.push_back(newBullet);
}

void FightGame::SpawnStar()
{
	for (vector<FlightStar*>::size_type i = 0; i < m_Star.size(); ++i)
	{
		if (!m_Star[i]->GetSpawn())
		{
			m_Star[i]->Init();
			if (m_bIsFever)
			{
				m_Star[i]->SetScore(SCORE_1400);
			}
			else
			{
				m_Star[i]->SetScore(SCORE_100);
			}
			JEngine::POINT tmpPoint = GetRandomPoint(m_Star[i]);
			m_Star[i]->Spawn(tmpPoint.x, tmpPoint.y);
			return;
		}
	}

	FlightStar* newStar = new FlightStar;
	newStar->Init();
	if (m_bIsFever)
	{
		newStar->SetScore(SCORE_1400);
	}
	else
	{
		newStar->SetScore(SCORE_100);
	}
	JEngine::POINT tmpPoint = GetRandomPoint(newStar);
	newStar->Spawn(tmpPoint.x, tmpPoint.y);
	m_Star.push_back(newStar);
}
