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

	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� WindowWidth, ���� WindowHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, WindowWidth, WindowHeight);
	// m_MemDC[MEMDCINDEX_MAIN]�� m_NewBitmap�� �����Ѵ�.
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
}

void GameManager::Release()
{
	delete m_Menu;
	delete m_Back;
	delete m_Player;
}

void GameManager::Update()
{
	// ������ �������� �ʾ����� MenuŬ������ Update�Լ��� �����Ѵ�.
	if (!m_Menu->GetGameStartFlag())
	{
		m_Menu->Update();
	}
	// ������ ������ ���
	else
	{
		m_CameraX = m_Player->GetPlayerX();
		m_Back->Update();
		m_Player->Update();

		// GetDC�� ���� DC�� �޴´�.
		HDC hdc = GetDC(m_hWnd);

		// ���� �׸� ���� ���� �������� hdc�� �׸���.
		BitBlt(hdc, 0, 0, WindowWidth, WindowHeight, m_MemDC, 0, 0, SRCCOPY);

		ReleaseDC(m_hWnd, hdc);
	}
}
