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
	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 ScreenWidth, 높이 ScreenHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, m_ScreenSize.cx, m_ScreenSize.cy);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 사용한 DC를 해제 한다.
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
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
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

	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, MaptoolWidth, MaptoolHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::DrawMenu()
{
	// 브러시 선택 및 이전 브러시 백업
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, m_GrayBrush);
}
