#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	m_bGameStart = false;
	m_bWin = false;
	m_bExit = false;
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;
	m_Score = 0;

	// Menu Ŭ���� ��ü ���� �Ҵ�
	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(m_hWnd, &m_bGameStart);

	// Field Ŭ���� �迭 ���� �Ҵ�
	if (m_Field != NULL)
	{
		delete[] m_Field;
	}
	m_Field = new Field[MaxField];
	for (int i = 0; i < MaxField; i++)
	{
		m_Field[i].Init(m_MemDC, &m_bWin);
	}
	m_FieldIndex = 0;

	// Player Ŭ���� ��ü ���� �Ҵ�
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(m_MemDC);

	// End Ŭ���� ��ü ���� �Ҵ�
	if (m_End != NULL)
	{
		delete m_End;
	}
	m_End = new End;
	m_End->Init(m_MemDC, m_Field->GetFieldWidth());

	// Front Ŭ���� ���� ���� �Ҵ�
	// ������ �޸� ũ�� ����
	m_Front.reserve(MaxFront);
	if (!m_Front.empty())
	{
		m_Front.clear();
	}
	for (int i = 0; i < MaxFront; i++)
	{
		Front* tmpFront = new Front;
		tmpFront->Init(m_MemDC);
		m_Front.push_back(tmpFront);
	}
	m_CurScoreFront = NULL;

	// Enemy Ŭ���� ����Ʈ
	if (!m_Enemy.empty())
	{
		m_Enemy.clear();
	}
	m_CurScoreEnemy = NULL;
	m_SpawnTime = 3000.0f;
	m_StartSpawnTimer = GetTickCount();
	m_CurSpawnTimer = 0.0f;

	m_CameraX = 0;
}

void GameManager::Release()
{
	delete m_Menu;
	delete[] m_Field;
	delete m_Player;
	delete m_End;

	// ������ ���Ҹ� �����Ѵ�.
	vector<Front*>::iterator iterFront;
	for (iterFront = m_Front.begin(); iterFront != m_Front.end(); ++iterFront)
	{
		delete (*iterFront);
	}
	m_Front.clear();
	// swap�� ����Ͽ� vector�� capacity�� 0 ���� �����.
	vector<Front*>().swap(m_Front);

	// ����Ʈ�� ���Ҹ� �����Ѵ�.
	list<Enemy*>::iterator iterEnemy;
	for (iterEnemy = m_Enemy.begin(); iterEnemy != m_Enemy.end(); ++iterEnemy)
	{
		delete (*iterEnemy);
	}
	m_Enemy.clear();
	// swap�� ����Ͽ� list�� �޸𸮸� �����Ѵ�.
	list<Enemy*>().swap(m_Enemy);

	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}

void GameManager::Update()
{
	if (!m_bGameStart)
	{
		m_Menu->Update();
	}
	else
	{
		// 2�ʿ��� 5�� ���̷� ��ȯ
		m_SpawnTime = ((rand() % 5) + 2) * 1000.0f;
		m_CurSpawnTimer = GetTickCount();

		// ���� ���
		TCHAR score[256];
		wsprintf(score, TEXT("    Score :     %d     "), m_Score);
		TextOut(m_MemDC, 900.0f, 100.0f, score, strlen(score));

		m_CameraX = m_Player->GetCameraX();
		m_FieldIndex = m_CameraX / m_Field->GetFieldWidth();

		for (int i = 0; i < 3; i++)
		{
			m_Field[m_FieldIndex + i].Update(&m_CameraX, m_FieldIndex + i);
		}

		for (vector<Front*>::size_type i = 0; i < m_Front.size(); ++i)
		{
			m_Front[i]->Update(&m_CameraX, i + 1, m_Field->GetFieldWidth());
		}

		if (m_FieldIndex >= 8)
		{
			m_End->Update(&m_CameraX);
		}

		// �ʳ��� �������� �ʾ��� ���
		if (m_CameraX < LastFieldWidth && (m_CurSpawnTimer - m_StartSpawnTimer >= m_SpawnTime))
		{
			if (m_Enemy.size() <= MaxEnemy)
			{
				Enemy* tmpEnemy = new Enemy;
				tmpEnemy->Init(m_MemDC);
				m_Enemy.push_back(tmpEnemy);
				m_StartSpawnTimer = m_CurSpawnTimer;
			}
		}
		// m_Enemy ����Ʈ�� ��� ���� ������ ����Ʈ ���� ��� Enemy�� Update�� �����ϰ� �պκ��� �׸���.
		if (!m_Enemy.empty())
		{
			list<Enemy*>::iterator iterEnemy;
			for (iterEnemy = m_Enemy.begin(); iterEnemy != m_Enemy.end(); ++iterEnemy)
			{
				(*iterEnemy)->Update(m_Player->GetState(), &m_CameraX, &m_bWin, &m_bExit);
				(*iterEnemy)->FrontDraw();
			}
		}

		m_Player->Update(&m_FieldIndex, &m_bWin, m_End->GetX(), m_End->GetY());

		// m_Enemy ����Ʈ�� ��� ���� ������ ����Ʈ ���� ��� Enemy�� �޺κ��� �׸���.
		if (!m_Enemy.empty())
		{
			bool bIsUnSpawn = false;
			list<Enemy*>::iterator iterEnemy;
			for (iterEnemy = m_Enemy.begin(); iterEnemy != m_Enemy.end(); ++iterEnemy)
			{
				(*iterEnemy)->BackDraw();
				// ���� ���� ���� �������� ��� ����Ʈ�� ù ���Ҹ� ���� �Ѵ�.
				if ((*iterEnemy)->GetX() <= -200.0f)
				{
					bIsUnSpawn = true;
				}
			}
			if (bIsUnSpawn)
			{
				m_Enemy.pop_front();
			}
		}

		// Front���� �浹
		for (vector<Front*>::size_type i = 0; i < m_Front.size(); ++i)
		{
			if (CheckCollision(m_Front[i]))
			{
				m_Player->Die();
				if (!m_bExit)
				{
					m_StartExitTimer = GetTickCount();
				}
				m_bExit = true;
			}

			if (CheckScoreCollision(m_Front[i]) && m_CurScoreFront != m_Front[i])
			{
				m_CurScoreFront = m_Front[i];
				m_Score += 100;
			}
		}

		// Enemy���� �浹
		list<Enemy*>::iterator iterEnemy;
		for (iterEnemy = m_Enemy.begin(); iterEnemy != m_Enemy.end(); ++iterEnemy)
		{
			if (CheckCollision(*iterEnemy))
			{
				m_Player->Die();
				if (!m_bExit)
				{
					m_StartExitTimer = GetTickCount();
				}
				m_bExit = true;
			}

			if (CheckScoreCollision(*iterEnemy) && m_CurScoreEnemy != *iterEnemy)
			{
				m_CurScoreEnemy = (*iterEnemy);
				m_Score += 100;
			}
		}

		// ������ Rect
		RECT tmpRect;

		// �¸�
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_End->GetCollision())))
		{
			if (!m_bWin)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bWin = true;
		}

		// ��ֹ��� �ɸ��ų� �¸��Ͽ��� �� ����ȭ������ �Ѿ��.
		m_CurExitTimer = GetTickCount();
		if ((m_bExit || m_bWin) && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
		{
			Init(m_hWnd);
		}

		// GetDC�� ���� DC�� �޴´�.
		HDC hdc = GetDC(m_hWnd);
		// ���� �׸� ���� ���� �������� hdc�� �׸���.
		BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hWnd, hdc);
	}
}

bool GameManager::CheckCollision(Object * obejct)
{
	// ������ Rect
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(obejct->GetCollision())))
	{
		return true;
	}

	return false;
}

bool GameManager::CheckScoreCollision(Object * obejct)
{
	// ������ Rect
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(obejct->GetScoreCollision())))
	{
		return true;
	}
	return false;
}
