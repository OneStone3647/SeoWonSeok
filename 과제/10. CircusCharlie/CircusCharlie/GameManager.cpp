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
	HDC hdc = GetDC(hWnd);

	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 WindowWidth, 높이 WindowHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, MaxField, WindowHeight);
	// m_MemDC[MEMDCINDEX_MAIN]에 m_NewBitmap을 연결한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	ReleaseDC(hWnd, hdc);

	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(hWnd);

	if (m_Back != NULL)
	{
		delete m_Back;
	}
	m_Back = new Back;
	m_Back->Init(m_MemDC);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(m_MemDC);

	if (m_End != NULL)
	{
		delete m_End;
	}
	m_End = new End;
	m_End->Init(m_MemDC);

	if (m_Enemy != NULL)
	{
		delete m_Enemy;
	}
	m_Enemy = new Enemy;
	m_Enemy->Init(m_MemDC);

	//if (!m_Enemy.empty())
	//{
	//	m_Enemy.clear();
	//}


	//if (m_Front != NULL)
	//{
	//	delete[] m_Front;
	//}
	//m_Front = new Front[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	m_Front[i].Init(m_MemDC);
	//}

	// 벡터의 메모리 크기 설정
	m_Front.reserve(3);
	if (!m_Front.empty())
	{
		m_Front.clear();
	}
	for (int i = 0; i < 3; i++)
	{
		Front* tmpFront = new Front;
		tmpFront->Init(m_MemDC);
		m_Front.push_back(tmpFront);
	}

	m_bIsWin = false;
	m_bIsExit = false;
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;
}

void GameManager::Release()
{
	delete m_Menu;
	delete m_Back;
	delete m_Player;
	delete m_End;		
	//delete[] m_Front;

	// 백터의 원소를 제거한다.
	m_Front.clear();
	// swap을 사용하여 vector의 capacity를 0 으로 만든다.
	vector<Front*>().swap(m_Front);

	//m_Enemy.clear();
}

void GameManager::Update()
{
	// 교집합 Rect
	RECT tmpRect;

	// 게임이 시작하지 않았으면 Menu클래스의 Update함수를 실행한다.
	if (!m_Menu->GetGameStartFlag())
	{
		m_Menu->Update();
	}
	// 게임이 시작할 경우
	else
	{
		m_CameraX = m_Player->GetCameraX();
		m_FieldIndex = m_CameraX / FieldWidth;

		m_Back->Update(m_CameraX, m_FieldIndex, m_bIsWin);
		m_End->Update(m_CameraX);
		m_Enemy->Update(m_CameraX, m_bIsExit);

		//for (int i = 0; i < 3; i++)
		//{
		//	if (m_FieldIndex >= 0)
		//	{
		//		m_Front[i].Update(m_CameraX, i);
		//	}
		//	if (m_FieldIndex >= 2)
		//	{
		//		m_Front[i].Update(m_CameraX, i + 3);
		//	}
		//	if (m_FieldIndex >= 5)
		//	{
		//		m_Front[i].Update(m_CameraX, i + 6);
		//	}
		//}

		vector<Front>::size_type i = 0;
		for (i; i < m_Front.size(); ++i)
		{
			if (m_FieldIndex >= 0)
			{
				m_Front[i]->Update(m_CameraX, i);
			}
			if (m_FieldIndex >= 2)
			{
				m_Front[i]->Update(m_CameraX, i + 2);
			}
			if (m_FieldIndex >= 4)
			{
				m_Front[i]->Update(m_CameraX, i + 4);
			}
			if (m_FieldIndex >= 6)
			{
				m_Front[i]->Update(m_CameraX, i + 6);
			}
		}

		m_Player->Update(m_FieldIndex, m_bIsWin, m_End->GetX(), m_End->GetY());

		// 장애물에 걸렸을 때
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Enemy->GetCollision()))
			|| CheckFrontHit())
		{
			m_Player->Die();
			if (!m_bIsExit)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bIsExit = true;
		}

		// 승리
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_End->GetCollision())))
		{
			if (!m_bIsWin)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bIsWin = true;
		}

		// 장애물에 걸리거나 승리하였을 때 메인화면으로 넘어간다.
		m_CurExitTimer = GetTickCount();
		if ((m_bIsExit || m_bIsWin) && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
		{
			Init(m_hWnd);
		}

		// GetDC를 통해 DC를 받는다.
		HDC hdc = GetDC(m_hWnd);

		// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
		BitBlt(hdc, -800, 0, MaxField, WindowHeight, m_MemDC, 0, 0, SRCCOPY);

		ReleaseDC(m_hWnd, hdc);
	}
}

// Front의 충돌 체크
bool GameManager::CheckFrontHit()
{
	// 교집합 Rect
	RECT tmpRect;

	//for (int i = 0; i < 3; i++)
	//{
	//	if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[i]->GetCollision())))
	//	{
	//		return true;
	//	}
	//}

	vector<Front>::size_type i = 0;
	for (i; i < m_Front.size(); ++i)
	{
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[i]->GetCollision())))
		{
			return true;
		}
	}

	return false;
}
