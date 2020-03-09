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
	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 ScreenWidth, 높이 ScreenHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 사용한 DC를 해제 한다.
	ReleaseDC(hWnd, hdc);

	m_bGameStart = false;
	m_bWin = false;
	m_bExit = false;
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;
	m_Score = 0;

	// Menu 클래스 객체 동적 할당
	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(m_hWnd, &m_bGameStart);

	// Field 클래스 배열 동적 할당
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

	// Player 클래스 객체 동적 할당
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(m_MemDC);

	// End 클래스 객체 동적 할당
	if (m_End != NULL)
	{
		delete m_End;
	}
	m_End = new End;
	m_End->Init(m_MemDC, m_Field->GetFieldWidth());

	// Front 클래스 백터 동적 할당
	// 벡터의 메모리 크기 설정
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
}

void GameManager::Release()
{
	delete m_Menu;
	delete[] m_Field;
	delete m_Player;
	delete m_End;

	// 백터의 원소를 제거한다.
	vector<Front*>::iterator iterFront;
	for (iterFront = m_Front.begin(); iterFront != m_Front.end(); ++iterFront)
	{
		delete (*iterFront);
	}
	m_Front.clear();
	// swap을 사용하여 vector의 capacity를 0 으로 만든다.
	vector<Front*>().swap(m_Front);

	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
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
		// 점수 출력
		TCHAR score[256];
		wsprintf(score, TEXT("    Score :     %d     "), m_Score);
		TextOut(m_MemDC, 900.0f, 100.0f, score, strlen(score));

		m_CameraX = m_Player->GetCameraX();
		m_FieldIndex = m_CameraX / m_Field->GetFieldWidth();
		
		// 디버그용 FieldIndex 출력
		TCHAR FieldIndex[256];
		wsprintf(FieldIndex, TEXT("    FieldIndex :     %d     "), m_FieldIndex);
		TextOut(m_MemDC, 1100.0f, 100.0f, FieldIndex, strlen(FieldIndex));

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

		m_Player->Update(&m_FieldIndex, &m_bWin, m_End->GetX(), m_End->GetY());

		// Front관련 충돌
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

		// 교집합 Rect
		RECT tmpRect;

		// 승리
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_End->GetCollision())))
		{
			if (!m_bWin)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bWin = true;
		}

		// 장애물에 걸리거나 승리하였을 때 메인화면으로 넘어간다.
		m_CurExitTimer = GetTickCount();
		if ((m_bExit || m_bWin) && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
		{
			Init(m_hWnd);
		}

		// GetDC를 통해 DC를 받는다.
		HDC hdc = GetDC(m_hWnd);
		// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
		BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hWnd, hdc);
	}
}

bool GameManager::CheckCollision(Object * obejct)
{
	// 교집합 Rect
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(obejct->GetCollision())))
	{
		return true;
	}

	return false;
}

bool GameManager::CheckScoreCollision(Object * obejct)
{
	// 교집합 Rect
	RECT tmpRect;
	if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(obejct->GetScoreCollision())))
	{
		return true;
	}
	return false;
}
