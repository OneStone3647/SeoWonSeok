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
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� BackScreenWidth, ���� WindowHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, BackScreenWidth, WindowHeight);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	// Menu Ŭ���� ���� �Ҵ�
	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(hWnd);
	m_bGameStart = false;
}

void GameManager::Release()
{
	delete m_Menu;
}

void GameManager::Update()
{
	if (!m_bGameStart)
	{
		m_Menu->Update(&m_bGameStart);
	}
	else
	{
		// GetDC�� ���� DC�� �޴´�.
		HDC hdc = GetDC(m_hWnd);
		// ���� �׸� ���� ���� �������� hdc�� �׸���.
		BitBlt(hdc, 0, 0, WindowWidth, WindowHeight, m_MemDC, 0, 0, SRCCOPY);
		ReleaseDC(m_hWnd, hdc);
	}
}
