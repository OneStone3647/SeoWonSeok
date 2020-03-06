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

	m_CameraX = -100.0f;
}

void GameManager::Release()
{
	delete m_Menu;
	delete[] m_Field;

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
		
		m_Field->Update(m_CameraX);

		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_CameraX -= 2.0f;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			m_CameraX += 2.0f;
		}

		// GetDC�� ���� DC�� �޴´�.
		HDC hdc = GetDC(m_hWnd);
		// ���� �׸� ���� ���� �������� hdc�� �׸���.
		BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hWnd, hdc);
	}
}
