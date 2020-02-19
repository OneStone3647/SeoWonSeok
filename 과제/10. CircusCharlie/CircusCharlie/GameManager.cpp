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

	// 실제로 보여야할 HDC와 HBITMAP
	m_MemDC[MEMDCINDEX_MAIN] = CreateCompatibleDC(hdc);
	m_NewBitmap[BITMAPINDEX_MAIN] = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	m_OldBitmap[BITMAPINDEX_MAIN] = (HBITMAP)SelectObject(m_MemDC[MEMDCINDEX_MAIN], m_NewBitmap[BITMAPINDEX_MAIN]);

	// 배경 관련 HDC와 HBITMAP
	m_MemDC[MEMDCINDEX_BACK] = CreateCompatibleDC(m_MemDC[MEMDCINDEX_MAIN]);
	m_NewBitmap[BITMAPINDEX_BACK] = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	m_OldBitmap[BITMAPINDEX_BACK] = (HBITMAP)SelectObject(m_MemDC[MEMDCINDEX_BACK], m_NewBitmap[BITMAPINDEX_BACK]);

	m_Back[BACKINDEX_BACK].Init(m_MemDC[MEMDCINDEX_BACK], "Bitmap\\back.bmp");
	m_Back[BACKINDEX_DECO].Init(m_MemDC[MEMDCINDEX_BACK], "Bitmap\\back_deco.bmp");
	m_Back[BACKINDEX_NORMAL1].Init(m_MemDC[MEMDCINDEX_BACK], "Bitmap\\back_normal.bmp");
	m_Back[BACKINDEX_NORMAL2].Init(m_MemDC[MEMDCINDEX_BACK], "Bitmap\\back_normal2.bmp");

	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(hWnd);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(hWnd);

	ReleaseDC(hWnd, hdc);
}

void GameManager::Release()
{
	for (int i = 0; i < 2; i++)
	{
		SelectObject(m_MemDC[i], m_OldBitmap[i]);
		DeleteObject(m_NewBitmap[i]);
		DeleteDC(m_MemDC[i]);
	}

	delete m_Menu;
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
		DrawBackGround();
		m_Player->Update();
	}
}

void GameManager::DrawBackGround()
{
	HDC hdc = GetDC(m_hWnd);

	// 바닥 그리기
	SIZE NewSize = m_Back[BACKINDEX_BACK].GetSize();
	for (int i = 0; i < 20; i++)
	{
		m_Back[BACKINDEX_BACK].DrawBack(m_MemDC[MEMDCINDEX_BACK], i * NewSize.cx, 300);
	}

	// 관중 그리기
	NewSize = m_Back[BACKINDEX_NORMAL1].GetSize();
	for (int i = 0; i < 21; i++)
	{
		m_Back[BACKINDEX_NORMAL1].DrawBack(m_MemDC[MEMDCINDEX_BACK], i*NewSize.cx, 236);
	}

	//
	NewSize = m_Back[BACKINDEX_DECO].GetSize();
	m_Back[BACKINDEX_DECO].DrawBack(m_MemDC[MEMDCINDEX_BACK], NewSize.cx, 233);

	// m_MemDC[MEMDCINDEX_BACK]에 그린 것을 m_MemDC[MEMDCINDEX_MAIN]에 그린다.
	BitBlt(m_MemDC[MEMDCINDEX_MAIN], 0, 0, ScreenWidth, ScreenHeight, m_MemDC[MEMDCINDEX_BACK], 0, 0, SRCCOPY);

	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC[MEMDCINDEX_MAIN], 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, hdc);
}
