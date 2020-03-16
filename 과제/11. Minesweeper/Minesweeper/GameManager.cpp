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

	// 배경 비트맵 초기화
	m_Back.Init(m_MemDC, "Bitmap\\back.bmp");

	// 블록 클래스 초기화
	m_Block.Init(m_MemDC);
}

void GameManager::Release()
{
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);
}

void GameManager::Update(LPARAM lParam)
{
	int startX = BlockStartX16;
	int startY = BlockStartY16;

	m_Back.Draw(m_MemDC, 0, 0, ScreenWidth30, ScreenHeight30);

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			m_Block.DrawBlock(BLOCKINDEX_BLANK, x * BlockSize + startX, y * BlockSize + startY, BlockSize, BlockSize);
		}
	}


	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::InitBlock()
{
}
