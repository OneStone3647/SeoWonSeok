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

	// 벡터의 메모리 크기 설정
	m_Back.reserve(3);
	if (!m_Back.empty())
	{
		m_Back.clear();
	}
	for (int i = 0; i < 3; i++)
	{
		Back* tmpBack = new Back;
		tmpBack->Init(m_MemDC);
		m_Back.push_back(tmpBack);
	}

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
	m_CurScoreFront = NULL;

	//if (m_Enemy != NULL)
	//{
	//	delete m_Enemy;
	//}
	//m_Enemy = new Enemy;
	//m_Enemy->Init(m_MemDC);

	m_bIsWin = false;
	m_bIsExit = false;
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;

	m_Score = 0;
}

void GameManager::Release()
{
	delete m_Menu;
	delete m_Player;
	//delete m_End;

	// 백터의 원소를 제거한다.
	m_Back.clear();
	// swap을 사용하여 vector의 capacity를 0 으로 만든다.
	vector<Back*>().swap(m_Back);

	// 백터의 원소를 제거한다.
	m_Front.clear();
	// swap을 사용하여 vector의 capacity를 0 으로 만든다.
	vector<Front*>().swap(m_Front);
}

void GameManager::Update()
{
	// 게임이 시작하지 않았으면 Menu클래스의 Update함수를 실행한다.
	if (!m_Menu->GetGameStartFlag())
	{
		m_Menu->Update();
	}
	// 게임이 시작할 경우
	else
	{
		TCHAR score[256];
		wsprintf(score, TEXT("    Score :     %d     "), m_Score);
		TextOut(m_MemDC, 900.0f, 100.0f, score, strlen(score));

		m_CameraX = m_Player->GetCameraX();
		m_FieldIndex = (m_CameraX + 500.0f) / FieldWidth;

		TCHAR FieldIndex[256];
		wsprintf(FieldIndex, TEXT("    FieldIndex :     %d     "), m_FieldIndex);
		TextOut(m_MemDC, 1100.0f, 100.0f, FieldIndex, strlen(FieldIndex));

		vector<Back>::size_type BackIndex = 0;
		for (BackIndex; BackIndex < m_Back.size(); ++BackIndex)
		{
			m_Back[BackIndex]->Update(m_CameraX, m_FieldIndex + BackIndex, m_bIsWin);
		}


		// 일정한 거리를 지나면 End 생성
		if (m_FieldIndex > 7)
		{
			m_End->Update(m_CameraX);
		}

		// Front 생성
		vector<Object>::size_type FrontIndex = 0;
		for (FrontIndex; FrontIndex < m_Front.size(); ++FrontIndex)
		{
			if (m_FieldIndex >= 0)
			{
				m_Front[FrontIndex]->Update(m_CameraX, FrontIndex);
			}
			if (m_FieldIndex >= 3)
			{
				m_Front[FrontIndex]->Update(m_CameraX, FrontIndex + 3);
			}
			//if (m_FieldIndex >= 6)
			//{
			//	m_Front[FrontIndex]->Update(m_CameraX, FrontIndex + 6);
			//}
		}

		//m_Enemy->Update(m_CameraX, m_bIsExit);

		// 플레이어 생성
		m_Player->Update(m_FieldIndex, m_bIsWin, m_End->GetX(), m_End->GetY());

		// 교집합 Rect
		RECT tmpRect;

		//// 장애물에 걸렸을 때
		//if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Enemy->GetCollision()))
		//	|| CheckFrontCollision())
		//{
		//	m_Player->Die();
		//	if (!m_bIsExit)
		//	{
		//		m_StartExitTimer = GetTickCount();
		//	}
		//	m_bIsExit = true;
		//}

		// 장애물에 걸렸을 때
		if (CheckFrontCollision())
		{
			m_Player->Die();
			if (!m_bIsExit)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bIsExit = true;
		}

		// 점수 증가
		if (CheckFrontScoreCollision())
		{
			m_Score += 100;
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
		BitBlt(hdc, -300, 0, MaxField, WindowHeight, m_MemDC, 0, 0, SRCCOPY);

		ReleaseDC(m_hWnd, hdc);
	}
}

// Front의 충돌 체크
bool GameManager::CheckFrontCollision()
{
	// 교집합 Rect
	RECT tmpRect;

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

bool GameManager::CheckFrontScoreCollision()
{
	// 교집합 Rect
	RECT tmpRect;

	vector<Front>::size_type i = 0;
	for (i; i < m_Front.size(); ++i)
	{
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[i]->GetScoreCollision())) && m_Front[i] != m_CurScoreFront)
		{
			m_CurScoreFront = m_Front[i];
			return true;
		}
	}

	return false;
}
