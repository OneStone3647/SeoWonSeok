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
	m_ExitTime = 2000.0f;
	m_StartExitTimer = 0.0f;
	m_CurExitTimer = 0.0f;

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
}

void GameManager::Release()
{
	delete m_Menu;
	delete[] m_Field;
	delete m_Player;
	delete m_End;

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
		if (m_bWin && (m_CurExitTimer - m_StartExitTimer >= m_ExitTime))
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
