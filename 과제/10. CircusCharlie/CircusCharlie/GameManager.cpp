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

	if (m_Front != NULL)
	{
		delete[] m_Front;
	}
	m_Front = new Front[3];
	for (int i = 0; i < 3; i++)
	{
		m_Front[i].Init(m_MemDC);
	}

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
	delete[] m_Front;

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

		m_Back->Update(m_CameraX, m_FieldIndex);
		m_End->Update(m_CameraX);
		m_Enemy->Update(m_CameraX, m_bIsExit);
		for (int i = 0; i < 3; i++)
		{
			if (m_FieldIndex >= 0)
			{
				m_Front[i].Update(m_CameraX, i);
			}
			if (m_FieldIndex >= 2)
			{
				m_Front[i].Update(m_CameraX, i + 3);
			}
			if (m_FieldIndex >= 5)
			{
				m_Front[i].Update(m_CameraX, i + 6);
			}
		}

		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 6; j += 3)
		//	{
		//		m_Front[i].Update(m_CameraX, i + j);
		//	}
		//}

		// 7까지
		//m_Front[0].Update(m_CameraX, 0);
		//m_Front[1].Update(m_CameraX, 1);
		//m_Front[2].Update(m_CameraX, 2);
		//m_Front[0].Update(m_CameraX, 3);
		//m_Front[1].Update(m_CameraX, 4);
		//m_Front[2].Update(m_CameraX, 5);
		//m_Front[0].Update(m_CameraX, 6);
		//m_Front[1].Update(m_CameraX, 7);

		m_Player->Update(m_FieldIndex, m_bIsExit, m_End->GetX(), m_End->GetY());

		// 장애물에 걸렸을 때
		if (IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Enemy->GetCollision()))
			|| IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[0].GetCollision()))
			|| IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[1].GetCollision()))
			|| IntersectRect(&tmpRect, &(m_Player->GetCollision()), &(m_Front[2].GetCollision())))
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
			if (!m_bIsExit)
			{
				m_StartExitTimer = GetTickCount();
			}
			m_bIsExit = true;
		}

		m_CurExitTimer = GetTickCount();
		if (m_bIsExit && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
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
