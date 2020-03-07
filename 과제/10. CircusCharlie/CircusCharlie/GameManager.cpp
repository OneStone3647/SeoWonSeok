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
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;

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
}

void GameManager::Release()
{
	delete m_Menu;
	delete[] m_Field;
	delete m_Player;
	delete m_End;

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
		//float m_Score = 100.0f;
		//TCHAR score[256];
		//wsprintf(score, TEXT("    Score :     %d     "), m_Score);
		//TextOut(m_MemDC, 900.0f, 100.0f, score, strlen(score));
		m_CameraX = m_Player->GetCameraX();
		m_FieldIndex = m_CameraX / m_Field->GetFieldWidth();		
		TCHAR FieldIndex[256];
		wsprintf(FieldIndex, TEXT("    FieldIndex :     %d     "), m_FieldIndex);
		TextOut(m_MemDC, 1100.0f, 100.0f, FieldIndex, strlen(FieldIndex));

		//TCHAR CameraX[256];
		//wsprintf(FieldIndex, TEXT("    CameraX :     %d     "), m_CameraX);
		//TextOut(m_MemDC, 900.0f, 100.0f, CameraX, strlen(CameraX));

		for (int i = 0; i < 3; i++)
		{
			m_Field[m_FieldIndex + i].Update(&m_CameraX, m_FieldIndex + i);
		}

		if (m_FieldIndex >= 8)
		{
			m_End->Update(&m_CameraX);
		}

		m_Player->Update(&m_FieldIndex, &m_bWin, m_End->GetX(), m_End->GetY());

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
		if (m_bWin && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
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
