#include "GameManager.h"

GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
	Release();
}

void GameManager::Init(HWND hWnd)
{
	m_ScreenSize.cx = GameWidth;
	m_ScreenSize.cy = GameHeight;

	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, m_ScreenSize.cx, m_ScreenSize.cy);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	MoveWindow(m_hWnd, WindowPosX, WindowPosY, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);

	m_GameStart = false;

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init();

	m_BlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_GrayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
}

void GameManager::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);

	if (m_Player != NULL)
	{
		delete m_Player;
	}

	DeleteObject(m_BlackBrush);
	DeleteObject(m_GrayBrush);
}

void GameManager::Update()
{
	if (!m_GameStart)
	{
		DrawMenu();
	}
	else
	{

	}

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, MaptoolWidth, MaptoolHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::DrawMenu()
{
	// �귯�� ���� �� ���� �귯�� ���
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_GrayBrush);
}
