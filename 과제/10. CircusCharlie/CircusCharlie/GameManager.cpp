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
	m_NewBitmap = CreateCompatibleBitmap(hdc, WindowWidth, WindowHeight);
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
}

void GameManager::Release()
{
	delete m_Menu;
	delete m_Back;
	delete m_Player;
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
		m_CameraX = m_Player->GetPlayerX();
		m_Back->Update();
		m_Player->Update();

		// GetDC를 통해 DC를 받는다.
		HDC hdc = GetDC(m_hWnd);

		// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
		BitBlt(hdc, 0, 0, WindowWidth, WindowHeight, m_MemDC, 0, 0, SRCCOPY);

		ReleaseDC(m_hWnd, hdc);
	}
}
